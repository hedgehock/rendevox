#include "rendevox.h"

SDL_Window *sdlWindow;

int createWindow(int width, int height, const char *title) {
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("ERROR: can't init SDL");
		return 1;
	}

	// Create window and renderer
	sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

	if (!sdlWindow) {
		printf("ERROR: can't create window");
		return 1;
	}


	// Init TTF
	if (TTF_Init() < 0) {
		printf("ERROR: can't init TTF");
		return 1;
	}

	// Call user start function
	start();
	
	// Create render entity buffer
	createRender(sdlWindow);

	SDL_Event sdlEvent;
	char running = 1;
	int deltaSeconds = 0;
	while (running == 1) {
		// Get start delta
		Uint32 deltaStart = SDL_GetTicks();

		// Detect if window should close
		while (SDL_PollEvent(&sdlEvent) == 1) {
			if (sdlEvent.type == SDL_QUIT) {
				running = 0;
			}
		}

		// Render
		render(deltaSeconds);

		// call user update function
		update(deltaSeconds);


		// Calculate deltaSeconds
		deltaSeconds = SDL_GetTicks() - deltaStart;
	}

	// Destroy entity buffer
	destroyRender();

	// Quit TTF
	TTF_Quit();

	// Quit SDL
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();

	return 0;
}
