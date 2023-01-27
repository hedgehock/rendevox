#include "rendevox.h"

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

GLFWwindow* vulkanWindow;

void createVulkanWindow(window window) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    vulkanWindow = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);
}

void initVulkan() {

}

void mainVulkanLoop() {

// GLFW window loop
    while (!glfwWindowShouldClose(vulkanWindow)) {
        glfwPollEvents();
    }
}

void cleanupVulkan() {
    glfwDestroyWindow(vulkanWindow);

    glfwTerminate();
}

void runVulkanApp(window window) {
    createVulkanWindow(window);
    initVulkan();
    mainVulkanLoop();
    cleanupVulkan();
}
