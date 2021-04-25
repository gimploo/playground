#include "init.h"
#include "draw.h"
#include "common.h"
#include "input.h"

void cleanup(void)
{
		SDL_Quit();
}

int main(void) 
{
		memset(&game, 0, sizeof(app_t));

		sdl_init();

		atexit(cleanup);

		while (true)
		{
				prepare_scene();
				input_handling();
				present_scene();
				SDL_Delay(16);
		}

		return 0;
}
