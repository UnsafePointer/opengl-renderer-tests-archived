#include "Renderer.hpp"
#include <iostream>
#include "Framebuffer.hpp"
#include "RendererDebugger.hpp"

using namespace std;

const uint32_t WIDTH = 1024;
const uint32_t HEIGHT = 768;

Renderer::Renderer() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    window = SDL_CreateWindow("renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        cout << "Failed to initialize the OpenGL context." << endl;
        exit(1);
    }
    cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << endl;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	framebufferTexture = make_unique<Texture>(WIDTH, HEIGHT);

    program = make_unique<RendererProgram>("C:\\Users\\Ruenzuo\\GitHub\\UnsafePointer\\opengl-renderer-tests\\glsl\\vertex.glsl", "C:\\Users\\Ruenzuo\\GitHub\\UnsafePointer\\opengl-renderer-tests\\glsl\\fragment.glsl");
    program->useProgram();

    buffer = make_unique<RendererBuffer<Vertex>>(program, 1024);

    

    screenProgram = make_unique<RendererProgram>("C:\\Users\\Ruenzuo\\GitHub\\UnsafePointer\\opengl-renderer-tests\\glsl\\screen_vertex.glsl", "C:\\Users\\Ruenzuo\\GitHub\\UnsafePointer\\opengl-renderer-tests\\glsl\\screen_fragment.glsl");

    screenBuffer = make_unique<RendererBuffer<Pixel>>(screenProgram, 1024);
    checkForOpenGLErrors();
}

Renderer::~Renderer() {
    SDL_Quit();
}

void Renderer::addPolygon(std::vector<Vertex> vertices) {
    buffer->addData(vertices);
}

void Renderer::prepareFrame() {
    framebufferTexture->bind(GL_TEXTURE0);
    checkForOpenGLErrors();
}

void Renderer::render() {
    Framebuffer framebuffer = Framebuffer(framebufferTexture);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    buffer->draw();
    checkForOpenGLErrors();
}

void Renderer::finishFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    std::vector<Pixel> pixels = {
         Pixel({-0.9f, 0.9f}, {0.0f, 1.0f}),
         Pixel({-0.9f, -0.9f}, {0.0f, 0.0f}),
         Pixel({0.9f,  -0.9f}, {1.0f, 0.0f}),
         Pixel({-0.9f,  0.9f}, {0.0f, 1.0f}),
         Pixel({0.9f,  -0.9f}, {1.0f, 0.0f}),
         Pixel({0.9f,  0.9f}, {1.0f, 1.0f})
    };
    screenBuffer->bind();
    screenProgram->useProgram();
    screenBuffer->addData(pixels);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture->object);
    screenBuffer->draw();
    SDL_GL_SwapWindow(window);
    checkForOpenGLErrors();
    return;
}
