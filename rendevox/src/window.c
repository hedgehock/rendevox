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
        delta = SDL_GetTicks() - start;
    }
}

void rvxCreateWindow(const char* renderType, int width, int height, const char* title, char fullscreen) {
    // Create window
    window mainWindow;
    createWindow(&mainWindow, "SDL2", width, height, title);

    // NOTE: Create render

    // Loop
    if (renderType == "SDL2") {
        sdl2Loop(mainWindow);
    }

    // Destroy window
    // NOTE: Destroy render
    destroyWindow(&mainWindow);
}

void createWindow(window *window, const char* renderType, int width, int height, const char *title) {
    // Set window parameters
    window->title = title;
    window->width = width;
    window->height = height;

    // Do stuff according to render tpe
    if (renderType == "SDL2") {
        // Init SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            printf("Can't init SDL");
            exit(EXIT_FAILURE);
        }

        // Create Window and Renderer
        window->sdl_window = SDL_CreateWindow(window->title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window->width, window->height, 0);
        window->sdl_renderer = SDL_CreateRenderer(window->sdl_window, 0, SDL_RENDERER_PRESENTVSYNC);

        // Catch errors
        if (!window->sdl_window) {
            printf("Can't create window");
            exit(EXIT_FAILURE);
        }
        if (!window->sdl_renderer) {
            printf("Can't create renderer");
            exit(EXIT_FAILURE);
        }

        // Set window title
        SDL_SetWindowTitle(window->sdl_window, title);

        // Init TTF
        if (TTF_Init() < 0) {
            printf("Can't init TTF");
            exit(EXIT_FAILURE);
        }
    }
}

void destroyWindow(window *window) {
    // DeInit TTF
    TTF_Quit();

    // DeInit SDL
    SDL_DestroyRenderer(window->sdl_renderer);
    SDL_DestroyWindow(window->sdl_window);
    SDL_Quit();
}
