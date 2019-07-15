#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "RendererProgram.hpp"
#include "RendererBuffer.hpp"
#include "Vertex.hpp"

class Renderer {
    SDL_GLContext glContext;
    SDL_Window *window;

    std::unique_ptr<RendererProgram> program;
    std::unique_ptr<RendererBuffer<Vertex>> buffer;
public:
    Renderer();
    ~Renderer();

    void addPolygon(std::vector<Vertex> vertices);
    void forceDraw();
};
