#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window
{
    public:
        Window(const char* title);
        Window(const char* title, int screen_width, int screen_height);
        ~Window();

        void SetSize(int width, int height);
        void GetSize();

        inline void Close() { glfwSetWindowShouldClose(this->m_window, true); }
        inline bool ShouldClose() { return glfwWindowShouldClose(this->m_window); }
        inline void SwapBuffers() { glfwSwapBuffers(this->m_window); }
        inline bool KeyPressed(int key) { return glfwGetKey(this->m_window, key) == GLFW_PRESS; }
        inline void MakeCurrent() { glfwMakeContextCurrent(this->m_window); }

    private:
        void initialize();

    private:
        GLFWwindow* m_window;

        int m_screen_width;
        int m_screen_height;

        const char* m_title;
};

#endif