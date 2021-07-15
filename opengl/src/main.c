#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define KB 1024

// comment this line not have opengl used for rendering
#include <GL/glew.h> 

//poglib repo
#include "../lib/simple/win/simple_window.h"


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

void gl_Draw_Triangle(float vertices[], size_t size)
{
    GLuint VAO;
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO); 

    GLuint VBO;
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    /*GLuint EBO;*/
    /*glGenBuffers(1, &EBO); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/
    /*glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);*/

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
}

void gl_Draw_Rectangle(float vertices[], size_t size, GLuint indices[], size_t indices_size)
{

    GLuint VAO;
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

int main(void) 
{
    float triangle[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    float rectangle[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left
    };

    GLuint rec_indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    SimpleWindow window = window_init(SDL_INIT_VIDEO);
    /*printf("GL version %s\n", glGetString(GL_VERSION)); */

    int result;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &result);
    printf("MAX # vertex attributes supported %i\n", result);

#ifdef __gl_h_
    GLuint shaderProgram = gl_Create_Shader(vertexShaderSource, fragmentShaderSource);
#endif


    bool toggle = false;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (window.is_window_open) 
    {
        window_event_process_user_input(&window);
        
    #ifdef __gl_h_
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);


        if (toggle)
            gl_Draw_Triangle(triangle, sizeof(triangle));
        else 
            gl_Draw_Rectangle(rectangle, sizeof(rectangle), rec_indices, sizeof(rec_indices));

        toggle = !toggle;

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
