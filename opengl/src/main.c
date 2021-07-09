#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// comment this line not have opengl used for rendering
#include <GL/glew.h> 

//poglib repo
#include "../lib/simple/simple_window.h"


int main(void) 
{
    
    SimpleWindow window = window_init(SDL_INIT_VIDEO);

    window_event_handler(&window);

    window_destroy(&window);

    
    return 0;
}
