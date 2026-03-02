cmake_minimum_required(VERSION 3.20)
project(GameEngine VERSION 0.1.0 LANGUAGES C CXX)

# 64-bit Erzwingen
if(MSVC)
    set(CMAKE_GENERATOR_PLATFORM x64 CACHE STRING "Target Platform" FORCE)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)

file(GLOB files_src
     "src/Core/*.hpp"
     "src/Core/*.cpp"
     "src/Core/*.c"
     "src/Core/objects/*.hpp"
     "src/Core/objects/*.cpp"
     "src/Core/graphics/*.hpp"
     "src/Core/graphics/*.cpp"
     "src/Core/components/*.hpp"
     "src/Core/components/*.cpp"
)

add_executable(GameEngine ${files_src})

target_include_directories(GameEngine PRIVATE include)

# Korrekte Verlinkung sicherstellen
if(TARGET GLFW3::GLFW3)
    target_link_libraries(GameEngine GLFW3::GLFW3 OpenGL::GL)
else()
    target_link_libraries(GameEngine ${GLFW3_LIBRARY} OpenGL::GL)
    if(GLFW3_INCLUDE_DIR)
        target_include_directories(GameEngine PRIVATE ${GLFW3_INCLUDE_DIR})
    endif()
endif()

set_property(TARGET GameEngine PROPERTY CXX_STANDARD 17)