#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "global.hpp"
#include "window.hpp"

#include "objects/triangle.hpp"

void process_input(Window* window);

std::vector<Object*> objects;

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

    Window win("OpelGL-Test", 800, 600);
    win.MakeCurrent();

    double last_time = glfwGetTime();
    double last_update_time = last_time;
    double delta = 0.0;
    int fps = 0;

    glm::vec3 camera_position(0.0f, 0.0f, 2.0f);
    glm::vec3 camera_view_direction(0.0f, 0.0f, -1.0f);

    glm::mat4 view = glm::lookAt(camera_position, camera_position + camera_view_direction, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.01f, 100.0f);

    Triangle triangle1(&view, &projection);
    objects.push_back(&triangle1);
    Shader shader("../shaders/shader.vert", "../shaders/shader.frag");

    while(!win.ShouldClose())
    {
        double current_time = glfwGetTime();
        delta += current_time - last_time;
        last_time = current_time;

        if(delta >= (1.0 / FPS))
        {
            process_input(&win);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            shader.Use();

            objects.at(0)->Draw(shader);

            win.SwapBuffers();
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

void process_input(Window *window)
{
    if(window->KeyDown(GLFW_KEY_ESCAPE))
    {
        window->Close();
    }

    if(window->KeyDown(GLFW_KEY_D))
    {
        objects.at(0)->Translate(glm::vec3(0.05f, 0.0f, 0.0f));
    }
    if(window->KeyDown(GLFW_KEY_A))
    {
        objects.at(0)->Translate(glm::vec3(-0.05f, 0.0f, 0.0f));
    }
    if(window->KeyDown(GLFW_KEY_W))
    {
        objects.at(0)->Translate(glm::vec3(0.0f, 0.05f, 0.0f));
    }
    if(window->KeyDown(GLFW_KEY_S))
    {
        objects.at(0)->Translate(glm::vec3(0.0f, -0.05f, 0.0f));
    }
}