#include "../include/rendevox.h"

void windowCreate(window* window) {
    if (strcmp(window->renderType, "OpenGL") == 0) {
        openglWindowRun(*window);
    }
    else if (strcmp(window->renderType, "Vulkan") == 0) {
        runVulkanApp(*window);
    }
}