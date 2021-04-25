#include "common.h"


void input_handling(void)
{
		SDL_Event event;
		
		while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
						exit(0);
						break;
				default:
						fprintf(stderr, "Error: input not handled\n");
						break;
				}
		}
}
