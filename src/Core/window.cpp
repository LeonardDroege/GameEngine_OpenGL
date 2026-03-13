#include "window.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(const char* title)
    : m_title(title), m_screen_width(800), m_screen_height(450)
{
    this->initialize();
}

Window::Window(const char* title, int screen_width, int screen_height)
    : m_title(title), m_screen_width(screen_width), m_screen_height(screen_height)
{
    this->initialize();
}

Window::~Window()
{
    glfwDestroyWindow(this->m_window);
}

void Window::initialize()
{
    this->m_window = glfwCreateWindow(this->m_screen_width, this->m_screen_height, this->m_title, nullptr, nullptr);
    if (this->m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    this->MakeCurrent();
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    } 

    glViewport(0, 0, this->m_screen_width, this->m_screen_height);
    glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);
}

void Window::SetSize(int width, int height)
{
    glfwSetWindowSize(this->m_window, width, height);
    this->m_screen_width = width;
    this->m_screen_height = height;
}

void Window::GetSize()
{
    glfwGetFramebufferSize(this->m_window, &this->m_screen_width, &this->m_screen_height);
}