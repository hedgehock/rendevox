#include "rendevox.h"

void createSdlWindow(window* window, const char* title) {
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

void destroySdlWindow(window *window) {
    // DeInit TTF
    TTF_Quit();

    // DeInit SDL
    SDL_DestroyRenderer(window->sdl_renderer);
    SDL_DestroyWindow(window->sdl_window);
    SDL_Quit();
}