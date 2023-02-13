#include <rendevox.h>

GLFWwindow* vulkanWindow;

vulkanString* requiredDeviceExtensions;
int requiredDeviceExtensionsCount;

VkInstance instance;
VkSurfaceKHR surface;

// Initializes Vulkan Physical Device (Destroyed on Vulkan instance cleanup)
VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
VkDevice logicalDevice;

// Destroyed on logical device destroy
VkQueue graphicsQueue;
VkQueue presentQueue;

void vulkanWindowRunVulkanApp(window window) {
    vulkanWindowCreateWindow(window);
    vulkanWindowInit();
    vulkanWindowMainLoop();
    vulkanWindowCleanup();
}

void vulkanWindowInit() {
    vulkanString extensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    requiredDeviceExtensions = extensions;
    requiredDeviceExtensionsCount = sizeof(extensions) / sizeof(vulkanString);

    vulkanWindowCreateInstance();
    vulkanWindowCreateSurface();
    vulkanWindowPickPhysicalDevice();
    vulkanWindowCreateLogicalDevice();
}

void vulkanWindowCreateWindow(window window) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    vulkanWindow = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);
}

void vulkanWindowMainLoop() {
    // GLFW window loop
    while (!glfwWindowShouldClose(vulkanWindow)) {
        glfwPollEvents();
    }
}

void vulkanWindowCleanup() {
    vkDestroyDevice(logicalDevice, NULL);
    vkDestroySurfaceKHR(instance, surface, NULL);
    vkDestroyInstance(instance, NULL);

    glfwDestroyWindow(vulkanWindow);
    glfwTerminate();
}

void vulkanWindowCreateInstance() {
    // Information about application
    VkApplicationInfo appInfo = {0};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "rendevox";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "rendevox";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Information about instance
    VkInstanceCreateInfo createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    // Get GLFW extensions
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    // Validation layer count (In newer versions of Vulkan are validation layers not required)
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
        vulkanError("Cannot create Vulkan instance!");
    }
}

void vulkanWindowPickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);

    if (deviceCount == 0) {
        vulkanError("Failed to find GPUs with Vulkan support!");
    }

    VkPhysicalDevice* devices = malloc(sizeof(VkPhysicalDevice) * deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices);

    // Choose suitable GPU
    for (int i = 0; i < deviceCount; i++) {
        if (vulkanWindowIsDeviceSuitable(devices[i])) {
            physicalDevice = devices[i];
            free(devices);
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        vulkanError("Failed to find suitable GPU!");
    }
}

bool vulkanWindowIsDeviceSuitable(VkPhysicalDevice device) {
    // Get GPU properties and features
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    bool extensionsSupported = vulkanWindowCheckDeviceExtensionSupport(device);

    bool swapChainAdequate;
    if (extensionsSupported) {
        vulkanWindowSwapChainSupportDetails swapChainSupport = vulkanWindowQuerySwapChainSupport(device);
        swapChainAdequate = swapChainSupport.formatsCount != 0 && swapChainSupport.presentModeCount != 0;
    }

    vulkanWindowQueueFamilyIndices indices = vulkanWindowFindQueueFamilies(device);

    // Support only for dedicated GPU and Integrated GPU with geometry shaders support and checks if GPU has required Queue families and supports required extensions
    return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ||
            deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) && deviceFeatures.geometryShader &&
           indices.is.GraphicsFamilyPresent && indices.is.PresentFamilyPresent && extensionsSupported &&
           swapChainAdequate;
}

// Function to find queue families
vulkanWindowQueueFamilyIndices vulkanWindowFindQueueFamilies(VkPhysicalDevice device) {
    vulkanWindowQueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);

    VkQueueFamilyProperties* queueFamilies = malloc(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);

    indices.is.GraphicsFamilyPresent = false;
    indices.is.PresentFamilyPresent = false;

    // Select Queue Family that supports VK_QUEUE_GRAPHICS_BIT
    for (int i = 0; i < queueFamilyCount; i++) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.family.GraphicsFamily = i;
            indices.is.GraphicsFamilyPresent = true;
            printf("This Queue Family at index %i supports graphics.\n", i);
        }

        if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
            printf("This Queue Family at index %i supports compute.\n", i);
        }

        if (queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT) {
            printf("This Queue Family at index %i supports transfer.\n", i);
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

        if (presentSupport) {
            indices.is.PresentFamilyPresent = true;
        }

        if (indices.is.GraphicsFamilyPresent && indices.is.PresentFamilyPresent) {
            break;
        }
    }

    return indices;
}

void vulkanWindowCreateLogicalDevice() {
    vulkanWindowQueueFamilyIndices indices = vulkanWindowFindQueueFamilies(physicalDevice);

    size_t queueFamilyCount = sizeof(indices.is) / sizeof(indices.is.GraphicsFamilyPresent);

    // Priority to influence the scheduling of command buffer from 0.0f to 1.0f
    float queuePriority = 1.0f;

    VkDeviceQueueCreateInfo firstQueue = {0};
    VkDeviceQueueCreateInfo secondQueue = {0};

    firstQueue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    firstQueue.queueFamilyIndex = indices.family.GraphicsFamily;
    firstQueue.queueCount = 1;
    firstQueue.pQueuePriorities = &queuePriority;

    secondQueue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    secondQueue.queueFamilyIndex = indices.family.PresentFamily;
    secondQueue.queueCount = 1;
    secondQueue.pQueuePriorities = &queuePriority;

    const VkDeviceQueueCreateInfo queueCreateInfos[] = {firstQueue, secondQueue};

    VkPhysicalDeviceFeatures deviceFeatures = {0};

    // Logical device info
    VkDeviceCreateInfo createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfos;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.queueCreateInfoCount = queueFamilyCount;
    createInfo.enabledLayerCount = 0;

    // Assign required device extensions to logical device
    createInfo.enabledExtensionCount = requiredDeviceExtensionsCount;
    createInfo.ppEnabledExtensionNames = (const char* const*) requiredDeviceExtensions;

    if (vkCreateDevice(physicalDevice, &createInfo, NULL, &logicalDevice) != VK_SUCCESS) {
        vulkanError("Failed to create logical device!");
    }

    // index 0 means use of one queue from family
    vkGetDeviceQueue(logicalDevice, indices.family.GraphicsFamily, 0, &graphicsQueue);
    vkGetDeviceQueue(logicalDevice, indices.family.PresentFamily, 0, &presentQueue);
}

void vulkanWindowCreateSurface() {
    if (glfwCreateWindowSurface(instance, vulkanWindow, NULL, &surface) != VK_SUCCESS) {
        vulkanError("Failed to create window surface!");
    }
}

bool vulkanWindowCheckDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionsCount;
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionsCount, NULL);

    VkExtensionProperties* availableExtensions = malloc(extensionsCount * sizeof(VkExtensionProperties));
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionsCount, availableExtensions);

    int supportedExtensionCount = 0;

    for (int r = 0; r < requiredDeviceExtensionsCount; r++) {
        for (int e = 0; e < extensionsCount; e++) {
            if (strcmp(requiredDeviceExtensions[r], availableExtensions[e].extensionName) == 0) {
                supportedExtensionCount++;
            }
        }
    }

    return supportedExtensionCount == requiredDeviceExtensionsCount;
}

vulkanWindowSwapChainSupportDetails vulkanWindowQuerySwapChainSupport(VkPhysicalDevice device) {
    vulkanWindowSwapChainSupportDetails details;

    // Get Query swap chain that device support if support
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &details.formatsCount, NULL);

    details.formats = malloc(sizeof(VkSurfaceFormatKHR) * details.formatsCount);

    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &details.formatsCount, details.formats);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &details.presentModeCount, NULL);

    details.presentModes = malloc(sizeof(VkPresentModeKHR) * details.presentModeCount);

    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &details.presentModeCount, details.presentModes);

    return details;
}

VkSurfaceFormatKHR chooseSwapSurfaceFormat(VkSurfaceFormatKHR* availableFormats, uint32_t formatsCount) {
    for (int i = 0; i < formatsCount; ++i) {
        if (availableFormats[i].format == VK_FORMAT_B8G8R8A8_SRGB &&
            availableFormats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormats[i];
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR chooseSwapPresentMode(VkPresentModeKHR* availablePresentModes, uint32_t presentModeCount) {
    for (int i = 0; i < presentModeCount; ++i) {
        if (availablePresentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentModes[i];
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities) {

}

// Vulkan error print with exit
void vulkanError(vulkanString errorMessage) {
    fprintf(stderr, "%s%s", errorMessage, "\n");
    exit(EXIT_FAILURE);
}
