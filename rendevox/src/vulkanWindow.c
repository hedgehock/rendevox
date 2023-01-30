#include "rendevox.h"

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

GLFWwindow* vulkanWindow;
VkInstance instance;

void vulkanRunApp(window window) {
    vulkanCreateWindow(window);
    vulkanInit();
    vulkanMainLoop();
    vulkanCleanup();
}

void vulkanInit() {
    vulkanCreateInstance();
    vulkanPickPhysicalDevice();
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
    appInfo.pApplicationName = "Hello triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
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
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
        fprintf(stderr, "%s", "Cannot create Vulkan instance!");
    }
}

void vulkanPickPhysicalDevice() {

    // Initializes Vulkan Physical Device (Destroyed on Vulkan instance cleanup)
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
}
