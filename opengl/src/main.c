#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define KB 1024

// comment this line not have opengl used for rendering
#include <GL/glew.h> 

//poglib repo
#include "../lib/simple/simple_window.h"


const char * const vertexShaderSource = 
    "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}";

const char * const fragmentShaderSource = 
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}";

GLuint gl_Create_Shader(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    int status;
    char error_log[KB];

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(vertexShader, KB, NULL, error_log);
        fprintf(stderr, "Error: %s\n", error_log);
        exit(1);
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(vertexShader, KB, NULL, error_log);
        fprintf(stderr, "Error: %s\n", error_log);
        exit(1);
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if(!status) {
        glGetProgramInfoLog(shaderProgram, KB, NULL, error_log);
        fprintf(stderr, "Error: %s\n", error_log);
        exit(1);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void gl_Draw_Triangle(float arr[], size_t arr_size)
{

    GLuint vertex_buffer_obj;
    glGenBuffers(1, &vertex_buffer_obj);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
    glBufferData(GL_ARRAY_BUFFER, arr_size, arr, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

}

int main(void) 
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    SimpleWindow window = window_init(SDL_INIT_VIDEO);
    /*printf("GL version %s\n", glGetString(GL_VERSION)); */

#ifdef __gl_h_
    GLuint shaderProgram = gl_Create_Shader(vertexShaderSource, 
#endif
                                            fragmentShaderSource);

    /*window_event_handler(&window);*/
    SDL_Event event;
    while (window.is_window_open) 
    {
        while(SDL_PollEvent(&event) > 0) 
        {
            switch (event.type) 
            {
                case SDL_QUIT:
                    window.is_window_open = false;
                    break;
            }

        }
    #ifdef __gl_h_
    

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        gl_Draw_Triangle(vertices, sizeof(vertices));

        SDL_GL_SwapWindow(window.window_handle);
    #else
        SDL_UpdateWindowSurface(window.window_handle);
    #endif
    }

#ifdef __gl_h_
    glDeleteProgram(shaderProgram);
#endif

    window_destroy(&window);

    
    return 0;
}
