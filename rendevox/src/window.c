#include "rendevox.h"

int calculateFps(int delta) {
    return round(1000.0f / (float)delta);
}

void sdl2Loop(window mainWindow) {
    // Create sdl event
    SDL_Event event;

    //font main_font = loadFont("../FreeSans.ttf");

    // Main loop
    char running = 0;
    int delta = 0;
    while (running == 0) {
        // Get start delta
        Uint32 start = SDL_GetTicks();

        // Input
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                running = 1;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(mainWindow.sdl_renderer, 0, 0, 0, 0);
        SDL_RenderClear(mainWindow.sdl_renderer);

        /*
        // Add to buffer
        render(main_window, delta);

        // Show FPS
        char fps_text[16] = "FPS: ";
        char fps_value[4];
        snprintf(fps_value, sizeof(fps_value), "%i", calculateFps(delta));
        strcat(fps_text, fps_value);
        drawText(main_window.sdl_renderer, 0, 0, fps_text, main_font);
         */

        // Render buffer
        SDL_RenderPresent(mainWindow.sdl_renderer);

        // Calculate delta
        delta = (int)(SDL_GetTicks() - start);
    }
}

void rvxCreateWindow(const char* renderType, int width, int height, const char* title, char fullscreen) {
    // Define Window
    window window;
    window.title = title;
    window.width = width;
    window.height = height;

    // Create window
    if (strcmp(renderType, "SDL2") == 0) {
        createSdlWindow(&window, title);
    }

    // Loop
    if (strcmp(renderType, "SDL2") == 0) {
        sdl2Loop(window);
    }

    // Destroy window
    if (strcmp(renderType, "SDL2") == 0) {
        destroySdlWindow(&window);
    }
}