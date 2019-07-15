#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "RendererProgram.hpp"
#include "RendererBuffer.hpp"
#include "Vertex.hpp"
#include "Texel.hpp"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_Window *window = SDL_CreateWindow("renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize the OpenGL context." << std::endl;
        exit(1);
    }
    std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

    std::unique_ptr<RendererProgram> program = std::make_unique<RendererProgram>("glsl/vertex.glsl", "glsl/fragment.glsl");
    program->useProgram();

    std::vector<Vertex> vertices = {
         Vertex(0.5f, -0.5f,  1.0f, 0.0f, 0.0f),
         Vertex(-0.5f, -0.5f,  0.0f, 1.0f, 0.0f),
         Vertex(0.0f,  0.5f,  0.0f, 0.0f, 1.0f)
    };
    RendererBuffer<Vertex> buffer = RendererBuffer<Vertex>(program, 1024);
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        buffer.addData(vertices);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        buffer.draw();
        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}
