#include "init.h"
#include "draw.h"
#include "common.h"
#include "input.h"

static entity_t car;

void	cleanup(void);
int main(void) 
{
		memset(&game, 0, sizeof(app_t));
		memset(&car, 0, sizeof(entity_t));

		sdl_init();

		car = (entity_t) {
				.x = 100,
				.y = 100,
				.texture = load_texture("../assets/delorean.png")
		};


		atexit(cleanup);

		while (true)
		{
				prepare_scene();
				input_handling();
				draw_texture(car.texture, car.x, car.y);
				present_scene();
				SDL_Delay(16);
		}

		return 0;
}

void cleanup(void)
{
		printf("[!] QUITING!\n");
		SDL_Delay(1000);
		SDL_DestroyTexture(car.texture);
		SDL_DestroyRenderer(game.renderer);
		SDL_DestroyWindow(game.window);
		SDL_Quit();
}
