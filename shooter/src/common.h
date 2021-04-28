#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>


#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT   720

typedef struct {
		SDL_Renderer *renderer;
		SDL_Window *window;
} app_t;

typedef struct {
		int x;
		int y;
		SDL_Texture *texture;
} entity_t;

app_t game;

#endif
