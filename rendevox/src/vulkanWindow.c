#include "rendevox.h"

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

GLFWwindow *vulkanWindow;
VkInstance instance;
VkDevice logicalDevice;

void runVulkanApp(window window) {
    vulkanCreateWindow(window);
    vulkanInit();
    vulkanMainLoop();
    vulkanCleanup();
}

void vulkanInit() {
    vulkanCreateInstance();
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
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
        fprintf(stderr, "%s", "Cannot create Vulkan instance!");
    }
}

void vulkanPickPhysicalDevice() {
    // Initializes Vulkan Physical Device (Destroyed on Vulkan instance cleanup)
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);

    if (deviceCount == 0) {
        fprintf(stderr, "%s", "Failed to find GPUs with Vulkan support!");
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
        fprintf(stderr, "%s", "Failed to find suitable GPU!");
    }
}

bool isDeviceSuitable(VkPhysicalDevice device) {
    // Get GPU properties and features
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    vulkanQueueFamilyIndices indices = findQueueFamilies(device);

    // Support only for dedicated GPU and Integrated GPU with geometry shaders support and checks if GPU has required Queue families
    return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ||
            deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) && deviceFeatures.geometryShader && indices.graphicsFamily;
}

vulkanQueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
    vulkanQueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);

    VkQueueFamilyProperties *queueFamilies = malloc(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);

    // Select Queue Family that supports VK_QUEUE_GRAPHICS_BIT
    for (int i = 1; i < queueFamilyCount + 1; i++) {
        if (queueFamilies[i - 1].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }
    }

    return indices;
}

void vulkanCreateLogicalDevice() {

}
