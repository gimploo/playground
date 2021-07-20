#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glew.h>

#include "../lib/simple/simple_window.h"
#include "../lib/image/bitmap.h"

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

void draw_xy_axis(void)
{
    float xy_axis[] = { 
        // x axis         
       -1.0, 0.0, 0.0,  1.0, 0.0, 0.0,    

        // y axis
        0.0, -1.0, 0.0, 0.0, 1.0, 0.0
    };

    GLuint VAO;
    GL_CHECK(glGenVertexArrays(1, &VAO)); 
    GL_CHECK(glBindVertexArray(VAO));

    GLuint VBO;
    GL_CHECK(glGenBuffers(1, &VBO));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(xy_axis), xy_axis, GL_STATIC_DRAW));

    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) (3 *sizeof(float)))); 


    // draws the 2 lines
    GL_CHECK(glDrawArrays(GL_LINES, 0, 4));

    // Unbinds the va and array buffer
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindVertexArray(0));

}

void loop(void)
{

    draw_xy_axis();

}

int main(void)
{
    SimpleWindow window = window_init(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_INIT_VIDEO);

    Shader shader = simple_use_default_shader();
    shader_use(&shader);

    BitMap bitmap = bitmap_init("res/font/charmap-oldschool_black.bmp");
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGB, 
        bitmap_get_width(&bitmap),
        bitmap_get_height(&bitmap),
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        (const void *)&bitmap
     );
    glGenerateMipmap(GL_TEXTURE_2D);
    bitmap_destroy(&bitmap);

    

    while (window.is_window_open)
    {
        window_process_user_input(&window);
        window_render(&window, loop);
    }

    window_destroy(&window);
    shader_destroy(&shader);

    return 0;
}
