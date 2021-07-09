#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "../lib/simple/open_window.h"


int main(void) 
{
    
    Window window = window_init(SDL_INIT_VIDEO);

    window_event_handler(&window);

    
    return 0;
}
