// #########################################################
// Coding Convention for this Project
// * Single lined comments
// * No HardCoding
// * Use Proper, Clean, and Well Spaced Syntax
// * variable name => snake_case
// * function name => camelCase
// * Class name    => PascalCase
// * // ########## <Comment> ##########

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>

// Function Definitions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);      // sets framebuffer size
void getInput(GLFWwindow* window);                                              // Receive input from user

// Constants
const unsigned int SCREEN_WIDTH = 1000;
const unsigned int SCREEN_HEIGHT = 750;

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

    Shader shader("../vertex.txt","../fragment.txt");

    // ########## SETTING UP VERTEX DATA AND VERTEX ATTRIBUTES ##########
    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind vertex array object, bind and set Buffers
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // ########## The Render Loop ##########
    while(!glfwWindowShouldClose(window))
    {
        // Taking Input
        getInput(window);

        // render
        glClearColor(0.1f, 0.2f, 0.3f, 0.9f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Drawing
        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw : swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // DEALLOCATE ALL RESOURCES
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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
