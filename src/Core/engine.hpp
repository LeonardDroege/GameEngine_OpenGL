#ifndef ENGINE_H
#define ENGINE_H

#include "window.hpp"
#include "global.hpp"
#include "graphics/shader.hpp"
#include <vector>
#include <functional>

class Engine
{
    public:
        Engine(const char* name, int initial_width, int initial_height);
        ~Engine();

        inline bool KeyDown(int key) { return m_current_window->KeyDown(key); }
        inline bool KeyUp(int key) { return m_current_window->KeyUp(key); }

        inline void AddRenderFunction(std::function<void(Engine*, Shader&)> fn) { this->m_render_functions.push_back(fn); }
        inline void AddUpdateFunction(std::function<void(Engine*)> fn) { this->m_update_functions.push_back(fn); }

        void Quit();

        void Update(Shader& shader);

    private:
        std::vector<Window> m_windows;
        Window* m_current_window;

        std::vector<std::function<void(Engine*)>> m_update_functions;
        std::vector<std::function<void(Engine*, Shader&)>> m_render_functions;

        void switch_window(unsigned int window_index);
        void update(Shader& shader);
        void show_fps(unsigned int fps);

        void render(Shader& shader);

        void process_updates();
};

#endif