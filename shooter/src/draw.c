#include "common.h"


void prepare_scene(void)
{
		SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
		SDL_RenderClear(game.renderer);
}

void present_scene(void)
{
		SDL_RenderPresent(game.renderer);
}

