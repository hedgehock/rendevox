#include "rendevox.h"

font main_font;

int calculateFps(int delta) {
    return round(1000.0f / (float)delta);
}

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

    main_font = sdlLoadFont("../resources/FreeSans.ttf");
}

// Create sdl event
SDL_Event event;

char running = 0;
int delta = 0;

void sdl2Loop(window window) {
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

        // -------------
        // Temp entities
        // -------------

        // Show FPS
        char fps_text[16] = "FPS: ";
        char fps_value[4];
        snprintf(fps_value, sizeof(fps_value), "%i", calculateFps(delta));
        strcat(fps_text, fps_value);
        drawText(window.sdlRenderer, 0, 0, fps_text, main_font);

        // Test triangle
        drawTriangle(window.sdlRenderer, (vector2){ 200.0f, 200.0f }, (vector2) { 300.0f, 300.0f},
                     (vector2){ 300.0f, 200.0f}, (color){ (char)255, (char)255, (char)255, (char)255});

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

void SDLRunApp(window window) {
    createSdlWindow(&window);
    sdl2Loop(window);
    destroySdlWindow(&window);
}