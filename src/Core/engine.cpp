#include "engine.hpp"

Engine::Engine(const char* name, int initial_width, int initial_height)
{
    this->m_windows.push_back(Window(name, initial_width, initial_height));
    this->switch_window(0);
    this->m_current_window->MakeCurrent();
}

Engine::~Engine()
{
    this->Quit();
}

void Engine::Update(Shader& shader)
{
    double current_time;
    double last_time = glfwGetTime();
    double delta = 0.0;
    double last_update_time = last_time;
    unsigned int fps = 0;

    while(!this->m_current_window->ShouldClose())
    {
        current_time = glfwGetTime();
        DeltaTime = current_time - last_time;
        delta += DeltaTime;
        last_time = current_time;

        if(delta >= (1.0 / FPS))
        {
            this->update(shader);
            fps++;
            delta--;
        }

        if(current_time - last_update_time >= 1.0)
        {
            this->show_fps(fps);
            fps = 0;
            last_update_time = current_time;
        }
    }

    glfwTerminate();
}

void Engine::Quit()
{
    for(auto& win : this->m_windows)
    {
        win.Close();
    }
    this->m_current_window = nullptr;
    this->m_windows.clear();
}

void Engine::switch_window(unsigned int window_index) 
{
    this->m_current_window = &this->m_windows.at(window_index);
    this->m_current_window->MakeCurrent();
}

void Engine::show_fps(unsigned int fps)
{
    std::cout << "FPS: " << fps << std::endl;
}

void Engine::update(Shader& shader)
{
    //update
    this->process_updates();

    //clearing screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
            
    //render
    this->render(shader);

    //update window and events
    this->m_current_window->SwapBuffers();
    glfwPollEvents();
}

void Engine::process_updates()
{
    for(auto& fn : this->m_update_functions)
    {
        fn(this);
    }
}

void Engine::render(Shader& shader)
{
    for(auto& fn : this->m_render_functions)
    {
        fn(this, shader);
    }
}