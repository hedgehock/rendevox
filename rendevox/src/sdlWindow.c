#include "rendevox.h"

void createSdlWindow(window* window) {
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Can't init SDL");
        exit(EXIT_FAILURE);
    }

    // Create Window and Renderer
    window->sdlWindow = SDL_CreateWindow(window->title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window->width, window->height, 0);
    window->sdlRenderer = SDL_CreateRenderer(window->sdlWindow, 0, SDL_RENDERER_PRESENTVSYNC);

    // Catch errors
    if (!window->sdlWindow) {
        printf("Can't create window");
        exit(EXIT_FAILURE);
    }
    if (!window->sdlRenderer) {
        printf("Can't create renderer");
        exit(EXIT_FAILURE);
    }

    // Init TTF
    if (TTF_Init() < 0) {
        printf("Can't init TTF");
        exit(EXIT_FAILURE);
    }
}

void sdl2Loop(window window) {
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
        SDL_SetRenderDrawColor(window.sdlRenderer, 0, 0, 0, 0);
        SDL_RenderClear(window.sdlRenderer);

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
        SDL_RenderPresent(window.sdlRenderer);

        // Calculate delta
        delta = (int)(SDL_GetTicks() - start);
    }
}

void destroySdlWindow(window *window) {
    // DeInit TTF
    TTF_Quit();

    // DeInit SDL
    SDL_DestroyRenderer(window->sdlRenderer);
    SDL_DestroyWindow(window->sdlWindow);
    SDL_Quit();
}

void runSDLApp(window window) {
    createSdlWindow(&window);
    sdl2Loop(window);
    destroySdlWindow(&window);
}