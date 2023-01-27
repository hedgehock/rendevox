#include "rendevox.h"

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

GLFWwindow* vulkanWindow;

void createVulkanWindow() {

}

void initVulkan() {

}

void mainVulkanLoop() {

}

void cleanupVulkan() {
    glfwDestroyWindow(vulkanWindow);
}

void runVulkanApp() {
    createVulkanWindow();
    initVulkan();
    mainVulkanLoop();
    cleanupVulkan();
}
