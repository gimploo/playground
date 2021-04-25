#include "common.h"


void sdl_init(void)
{
		int render_flags = SDL_RENDERER_ACCELERATED;

		// Initializing sdl
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
				fprintf(stderr, "Error: sdl initilization failed\n");
				exit(1);
		}		

		// Creating a window
		game.window = SDL_CreateWindow("S H O O T E R", 
										SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
										SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		if (!game.window) {
				fprintf(stderr, "Error: sdl failed to create window\n");
				exit(1);
		}

		// What is this?
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

		// Creating a renderer
		// Here -1 tells SDL to use the first graphics acclereation device it finds
		game.renderer = SDL_CreateRenderer(game.window, -1, render_flags);
		if (!game.renderer) {
				fprintf(stderr, "Error: sdl failed to create renderer\n");
				exit(1);
		}
		
}
