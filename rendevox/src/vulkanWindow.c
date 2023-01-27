#include "rendevox.h"

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

uint32_t WIDTH;
uint32_t HEIGHT;

GLFWwindow* vulkanWindow;

void createVulkanWindow() {
    glfwInit();

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
