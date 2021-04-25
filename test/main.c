#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

int main(int argc, char* argv[]) 
{
    bool is_window_open = true;

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Window *window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, 0);
    if (!window) {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return -1;
    }
    
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    if (!surface) {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Event event;
    while (is_window_open) 
    {
        while(SDL_PollEvent(&event) > 0) 
        {
            switch (event.type) 
            {
                case SDL_QUIT:
                    is_window_open = false;
                    break;
            }
            SDL_UpdateWindowSurface(window);
        }
    }
    
    return 0;
}
