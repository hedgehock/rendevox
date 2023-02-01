#include "rendevox.h"

void rvxCreateWindow(const char* renderType, int width, int height, const char* title, char fullscreen) {
    // Define Window
    window window;
    window.title = title;
    window.width = width;
    window.height = height;

    // Create window
    if (strcmp(renderType, "OpenGL") == 0) {
        runOpenGLApp(window);
    }
    else if (strcmp(renderType, "Vulkan") == 0) {
        runVulkanApp(window);
    }
    else if (strcmp(renderType, "SDL2") == 0) {
        runSDLApp(window);
    }
}