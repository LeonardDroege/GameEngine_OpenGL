#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "global.hpp"

#include "objects/triangle.hpp"

#include <iostream>

int screen_width = 800, screen_height = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void process_input(GLFWwindow *window);

std::vector<Object> objects;

int main()
{
    if(glfwInit() != GLFW_TRUE)
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "OpenGL-Test", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    } 

    glViewport(0, 0, screen_width, screen_height);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    double last_time = glfwGetTime();
    double last_update_time = last_time;
    double delta = 0.0;
    int fps = 0;

    glm::vec3 camera_position(0.0f, 0.0f, 2.0f);
    glm::vec3 camera_view_direction(0.0f, 0.0f, -1.0f);

    glm::mat4 view = glm::lookAt(camera_position, camera_position + camera_view_direction, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)screen_width / (float)screen_height, 0.01f, 100.0f);

    Triangle triangle1(&view, &projection);
    objects.push_back(triangle1);
    Shader shader("../shaders/shader.vert", "../shaders/shader.frag");

    while(!glfwWindowShouldClose(window))
    {
        double current_time = glfwGetTime();
        delta += current_time - last_time;
        last_time = current_time;

        if(delta >= (1.0 / FPS))
        {
            process_input(window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            shader.Use();

            triangle1.Draw(shader);

            glfwSwapBuffers(window);
            glfwPollEvents();

            delta = 0;
            fps++;
        }

        if(current_time - last_update_time >= 1.0)
        {
            std::cout << "FPS: " << fps << std::endl;
            fps = 0;
            last_update_time = current_time;
        }
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    screen_width = width;
    screen_height = height;
    glViewport(0, 0, width, height);
} 

void process_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        objects.at(0).Translate(glm::vec3(0.05f, 0.0f, 0.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        objects.at(0).Translate(glm::vec3(-0.05f, 0.0f, 0.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        objects.at(0).Translate(glm::vec3(0.0f, 0.05f, 0.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        objects.at(0).Translate(glm::vec3(0.0f, -0.05f, 0.0f));
    }
}