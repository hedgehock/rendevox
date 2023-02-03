#include "rendevox.h"

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

GLFWwindow *vulkanWindow;

const char *deviceExtensions;

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
    deviceExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

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
    const char **glfwExtensions;

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

    VkPhysicalDevice *devices = malloc(sizeof(VkPhysicalDevice) * deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices);

    // Choose suitable GPU
    for (int i = 0; i < deviceCount; i++) {
        if (isDeviceSuitable(devices[i])) {
            physicalDevice = devices[i];
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

    bool extensionsSupported = checkDeviceExtensionSupport(device);

    vulkanQueueFamilyIndices indices = findQueueFamilies(device);

    // Support only for dedicated GPU and Integrated GPU with geometry shaders support and checks if GPU has required Queue families and supports required extensions
    return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ||
            deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) && deviceFeatures.geometryShader &&
           indices.is.GraphicsFamilyPresent && indices.is.PresentFamilyPresent && extensionsSupported;
}

// Function to find queue families
vulkanQueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
    vulkanQueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);

    VkQueueFamilyProperties *queueFamilies = malloc(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
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

    VkDeviceQueueCreateInfo *queueCreateInfos = malloc(queueFamilyCount * sizeof(VkDeviceQueueCreateInfo));

    VkDeviceQueueCreateInfo queueInfo = {0};
    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.queueFamilyIndex = indices.family.GraphicsFamily;
    queueInfo.queueCount = 1;

    // Priority to influence the scheduling of command buffer from 0.0f to 1.0f
    float queuePriority = 1.0f;
    queueInfo.pQueuePriorities = &queuePriority;

    queueCreateInfos[0] = queueInfo;

    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.queueFamilyIndex = indices.family.PresentFamily;
    queueInfo.queueCount = 1;
    queueInfo.pQueuePriorities = &queuePriority;

    queueCreateInfos[1] = queueInfo;

    VkPhysicalDeviceFeatures deviceFeatures = {0};

    // Logical device info
    VkDeviceCreateInfo createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = (const VkDeviceQueueCreateInfo *) queueCreateInfos;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.queueCreateInfoCount = queueFamilyCount;
    createInfo.enabledLayerCount = 0;

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

bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionsCount;
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionsCount, NULL);

    VkExtensionProperties* availableExtensions = malloc(extensionsCount * sizeof(VkExtensionProperties));
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionsCount, availableExtensions);

    VkExtensionProperties* requiredExtensions = malloc(sizeof(VkExtensionProperties));

    for (int i = 0; i < extensionsCount; i++) {
        requiredExtensions = realloc(requiredExtensions, sizeof(VkExtensionProperties) * (i + 1));
        requiredExtensions[i] = availableExtensions[i];
    }

    return true;
}

// Vulkan error print with exit
void vulkanError(char *errorMessage) {
    fprintf(stderr, "%s%s", errorMessage, "\n");
    exit(EXIT_FAILURE);
}
