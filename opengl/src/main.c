#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


// comment this line not have opengl used for rendering
#include <GL/glew.h> 

//poglib repo
#include "../lib/simple/simple_window.h"
/*#include "../lib/image/bitmap.h"*/


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
    "uniform vec4 u_color;\n"
    "\n"
    "void main()\n"
    "{\n"
        "FragColor = u_color;\n"
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

    //NOTE: the 5th argument is the size of the vertex being passed into the shader
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

void gl_Draw_Rainbow_Triangle(void)
{
    
    float vertices[] = {
        // positions         // colors
        -0.25f, -0.25f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
         0.25f, -0.25f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.25f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };
    /*float vertices[] = {*/
        /*// positions         // colors*/
         /*0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right*/
        /*-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left*/
         /*0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top */
    /*};*/


    GLuint VAO;
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 *sizeof(float)));


    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

}

GLuint gl_Gen_2D_Texture(const char *file_path)
{
    BitMap bitmap = bitmap_init(file_path);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGB, 
        bitmap_get_width(&bitmap),
        bitmap_get_height(&bitmap),
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        &bitmap.pixels
     );
    glGenerateMipmap(GL_TEXTURE_2D);
    bitmap_destroy(&bitmap);

    return texture;
}

void gl_draw_textured_rectangle()
{
    float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    size_t size = sizeof(vertices);
    GLuint VAO;
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 4);

    glBindVertexArray(0);
}



int main(void) 
{
    float triangle[] = {
        -0.5f, -0.5f, 0.0f, // left 
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
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

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600
    
    SimpleWindow window = window_init(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_INIT_VIDEO);

    /*printf("GL version %s\n", glGetString(GL_VERSION)); */

    /*int result;*/
    /*glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &result);*/
    /*printf("MAX # vertex attributes supported %i\n", result);*/

#ifdef __gl_h_
    /*GLuint shaderProgram = gl_Create_Shader(vertexShaderSource, fragmentShaderSource);*/
    /*Shader prog = shader_init("src/rainbow.vs", "src/rainbow.fg"); */
    /*Shader prog = shader_init("src/wood.vs", "src/wood.fg"); */
    GLuint texture = gl_Gen_2D_Texture("res/sample.bmp");
#endif



    bool toggle = true;

    /*
     * Wireframe rendering
     */
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (window.is_window_open) 
    {
        window_process_user_input(&window);
        
    #ifdef __gl_h_
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* --------------------------------------------------------
         *
         * UNIFORMS
         *
         * --------------------------------------------------------
#include <math.h>
        # this is available in the shader header file
        float timeval = SDL_GetTicks();
        printf("time %lf\n", timeval);
        float greenval = (sin(timeval) / 2.0f + 0.5f);
        int frag_color_loc = glGetUniformLocation(shaderProgram, "u_color");
        glUniform4f(frag_color_loc, 0.0f, greenval, 0.0f, 1.0f);
        // --------------------------------------------------------
        */


        /*
        glUseProgram(shaderProgram);
        if (toggle)
            gl_Draw_Triangle(triangle, sizeof(triangle));
        else 
            gl_Draw_Rectangle(rectangle, sizeof(rectangle), rec_indices, sizeof(rec_indices));

        toggle = !toggle;
        */

        /*
         * Drawing a rainbow colored triangle with 2 attributes
         * enabled
         */
        /*shader_use(&prog);*/
        /*gl_Draw_Rainbow_Triangle();*/


        /*shader_use(&prog);*/
        glBindTexture(GL_TEXTURE_2D, texture);  
        gl_draw_textured_rectangle();

        SDL_GL_SwapWindow(window.window_handle);
    #else
        SDL_UpdateWindowSurface(window.window_handle);
    #endif
    }

#ifdef __gl_h_
    /*glDeleteProgram(shaderProgram);*/
    /*shader_destroy(&prog);*/
#endif

    window_destroy(&window);

    
    return 0;
}
