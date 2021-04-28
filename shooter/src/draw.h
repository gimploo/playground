#ifndef DRAW_H
#define DRAW_H
#include "common.h"

void			prepare_scene(void);
void			present_scene(void);
void			draw_texture(SDL_Texture *texture, int x, int y);
SDL_Texture *	load_texture(const char *filename);

#endif
