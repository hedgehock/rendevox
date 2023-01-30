#include "rendevox.h"

void rvxCreateWindow(const char* renderType, int width, int height, const char* title, char fullscreen) {
    // Define Window
    window window;
    window.title = title;
    window.width = width;
    window.height = height;

    // Create window
    if (strcmp(renderType, "SDL2") == 0) {
        SDLRunApp(window);
    } else if (strcmp(renderType, "Vulkan") == 0) {
        vulkanRunApp(window);
    }
}