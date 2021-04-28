#include "draw.h"

void prepare_scene(void)
{
		SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
		SDL_RenderClear(game.renderer);
}

void present_scene(void)
{
		SDL_RenderPresent(game.renderer);
}

SDL_Texture * load_texture(const char *filename)
{
		SDL_Texture *texture;
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,\
					   	SDL_LOG_PRIORITY_INFO, "Loading %s\n",\
					   	filename);

		texture = IMG_LoadTexture(game.renderer, filename);
		return texture;
}

void draw_texture(SDL_Texture *texture, int x, int y)
{
		if (texture == NULL) {
				fprintf(stderr, "Error: texture is null\n");
				exit(1);
		}

		SDL_Rect dest = {
				.x = x,
				.y = y,
		};

		SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
		SDL_RenderCopy(game.renderer, texture, NULL, &dest);
}

