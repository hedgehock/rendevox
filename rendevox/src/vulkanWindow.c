#include "rendevox.h"

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

GLFWwindow* vulkanWindow;

char* requiredDeviceExtensions;
int requiredDeviceExtensionsCount;

VkInstance instance;
VkSurfaceKHR surface;

// Initializes Vulkan Physical Device (Destroyed on Vulkan instance cleanup)
VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
VkDevice logicalDevice;

// Destroyed on logical device destroy
VkQueue graphicsQueue;
VkQueue presentQueue;

void runVulkanApp(window window) {
    vulkanCreateWindow(window);
    vulkanInit();
    vulkanMainLoop();
    vulkanCleanup();
}

void vulkanInit() {
    char* extensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    requiredDeviceExtensions = extensions;
    requiredDeviceExtensionsCount = sizeof(extensions) / sizeof(string);

    vulkanCreateInstance();
    vulkanCreateSurface();
    vulkanPickPhysicalDevice();
    vulkanCreateLogicalDevice();
}

void vulkanCreateWindow(window window) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    vulkanWindow = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);
}

void vulkanMainLoop() {
    // GLFW window loop
    while (!glfwWindowShouldClose(vulkanWindow)) {
        glfwPollEvents();
    }
}

void vulkanCleanup() {
    vkDestroyDevice(logicalDevice, NULL);
    vkDestroySurfaceKHR(instance, surface, NULL);
    vkDestroyInstance(instance, NULL);

    glfwDestroyWindow(vulkanWindow);
    glfwTerminate();
}

void vulkanCreateInstance() {
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


void vulkanPickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);

    if (deviceCount == 0) {
        vulkanError("Failed to find GPUs with Vulkan support!");
    }

    VkPhysicalDevice* devices = malloc(sizeof(VkPhysicalDevice) * deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices);

    // Choose suitable GPU
    for (int i = 0; i < deviceCount; i++) {
        if (isDeviceSuitable(devices[i])) {
            physicalDevice = devices[i];
            free(devices);
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        vulkanError("Failed to find suitable GPU!");
    }
}

bool isDeviceSuitable(VkPhysicalDevice device) {
    // Get GPU properties and features
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    bool extensionsSupported = vulkanCheckDeviceExtensionSupport(device);

    bool swapChainAdequate;
    if (extensionsSupported) {
        vulkanSwapChainSupportDetails swapChainSupport = vulkanQuerySwapChainSupport(device);
        swapChainAdequate = swapChainSupport.formatCount != 0 && swapChainSupport.presentModeCount != 0;
    }

    vulkanQueueFamilyIndices indices = findQueueFamilies(device);

    // Support only for dedicated GPU and Integrated GPU with geometry shaders support and checks if GPU has required Queue families and supports required extensions
    return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ||
            deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) && deviceFeatures.geometryShader &&
           indices.is.GraphicsFamilyPresent && indices.is.PresentFamilyPresent && extensionsSupported &&
           swapChainAdequate;
}

// Function to find queue families
vulkanQueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
    vulkanQueueFamilyIndices indices;

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

void vulkanCreateLogicalDevice() {
    vulkanQueueFamilyIndices indices = findQueueFamilies(physicalDevice);

    size_t queueFamilyCount = sizeof(indices.is) / sizeof(indices.is.GraphicsFamilyPresent);

    VkDeviceQueueCreateInfo* queueCreateInfos = calloc(queueFamilyCount, sizeof(VkDeviceQueueCreateInfo));

    // Priority to influence the scheduling of command buffer from 0.0f to 1.0f
    float queuePriority = 1.0f;

    queueCreateInfos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfos[0].queueFamilyIndex = indices.family.GraphicsFamily;
    queueCreateInfos[0].queueCount = 1;
    queueCreateInfos[0].pQueuePriorities = &queuePriority;

    queueCreateInfos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfos[1].queueFamilyIndex = indices.family.PresentFamily;
    queueCreateInfos[1].queueCount = 1;
    queueCreateInfos[1].pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures = {0};

    // Logical device info
    VkDeviceCreateInfo createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = (const VkDeviceQueueCreateInfo*) queueCreateInfos;
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

void vulkanCreateSurface() {
    if (glfwCreateWindowSurface(instance, vulkanWindow, NULL, &surface) != VK_SUCCESS) {
        vulkanError("Failed to create window surface!");
    }
}

bool vulkanCheckDeviceExtensionSupport(VkPhysicalDevice device) {
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

vulkanSwapChainSupportDetails vulkanQuerySwapChainSupport(VkPhysicalDevice device) {
    vulkanSwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &details.formatCount, details.formats);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &details.presentModeCount, details.presentModes);

    return details;
}

// Vulkan error print with exit
void vulkanError(char* errorMessage) {
    fprintf(stderr, "%s%s", errorMessage, "\n");
    exit(EXIT_FAILURE);
}
