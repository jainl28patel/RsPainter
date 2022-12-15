// #########################################################
// Coding Convention for this Project
// * Single lined comments
// * No HardCoding
// * Use Proper, Clean, and Well Spaced Syntax
// * variable name => snake_case
// * function name => camelCase
// * Class name    => PascalCase
// * // ########## <Comment> ##########

#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <KHR/khrplatform.h>

// Function Definitions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);      // sets framebuffer size
void getInput(GLFWwindow* window);                                              // Receive input from user
void checkCompileError(unsigned int shader_id);                                 // Checks Compilation ERRORS
void checkLinkingError(unsigned int program_id);                                // Checks Linking ERRORS

// Constants
const unsigned int SCREEN_WIDTH = 1000;
const unsigned int SCREEN_HEIGHT = 750;

// Temporary Vertex and Pixel Shaders
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 color;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = color;\n"
                                   "}\n\0";


int main() {

    // ########## glfw: initialize and configure ##########
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // ########## glfw window creation ##########
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raspainter", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ########## Checking if GLAD initialized or not ##########
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // ########## BUILD, COMPILE AND LINK SHADER PROGRAM ##########

    // ##### VERTEX SHADER #####
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertex_shader);
    checkCompileError(vertex_shader);

    // ##### PIXEL SHADER #####
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragment_shader);
    checkCompileError(fragment_shader);

    // ##### LINKING SHADERS #####
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    checkLinkingError(shader_program);

    // ##### DELETING SHADERS #####
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);


    // ########## SETTING UP VERTEX DATA, VERTEX BUFFERS AND VERTEX ARRAY OBJECTS ##########
    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind vertex array object, bind and set Buffers
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbinding buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // ########## The Render Loop ##########
    while(!glfwWindowShouldClose(window))
    {
        // Taking Input
        getInput(window);

        // render
        glClearColor(0.1f, 0.2f, 0.3f, 0.9f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Drawing
        glUseProgram(shader_program);

        // updating the color
        float time = glfwGetTime();
        // float r = sin(time)/2.0f + 0.5f;
        float color[4] = {sin(time)/2.0f + 0.5f, sin(time + 1)/2.0f + 0.5f, sin(time + 2)/2.0f + 0.5f, sin(time + 3)/2.0f + 0.5f};
        int color_uniform_location = glGetUniformLocation(shader_program, "color");
        glUniform4f(color_uniform_location, color[0], color[1], color[2], color[3]);

        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw : swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // DEALLOCATE ALL RESOURCES
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader_program);

    // TERMINATE ALL ALLOCATED RESOURCES TO GLFW
    glfwTerminate();
    return 0;
}

// ########## specifies the actual window rectangle for rendering ##########
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// ########## Gets User Input ##########
// Whenever the window size changed this function is called
void getInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void checkCompileError(unsigned int shader_id)
{
    int success;
    char info_log[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader_id, 512, NULL, info_log);
        std::cout << "COMPILATION ERROR : " << info_log << std::endl;
    }
}

void checkLinkingError(unsigned int program_id)
{
    int success;
    char info_log[512];
    glGetShaderiv(program_id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(program_id, 512, NULL, info_log);
        std::cout << "COMPILATION ERROR : " << info_log << std::endl;
    }
}
