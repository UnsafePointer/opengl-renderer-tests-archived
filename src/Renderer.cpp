#include "Renderer.hpp"
#include <iostream>

using namespace std;

Renderer::Renderer() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    window = SDL_CreateWindow("renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        cout << "Failed to initialize the OpenGL context." << endl;
        exit(1);
    }
    cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << endl;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    program = make_unique<RendererProgram>("glsl/vertex.glsl", "glsl/fragment.glsl");
    program->useProgram();

    buffer = make_unique<RendererBuffer<Vertex>>(program, 1024);
}

Renderer::~Renderer() {
    SDL_Quit();
}

void Renderer::addPolygon(std::vector<Vertex> vertices) {
    buffer->addData(vertices);
}

void Renderer::forceDraw() {
    glClear(GL_COLOR_BUFFER_BIT);
    buffer->draw();
    SDL_GL_SwapWindow(window);
}
