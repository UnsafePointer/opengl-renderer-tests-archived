#pragma once
#include <glad/glad.h>
#include <memory>
#include <vector>
#include "VertexArrayObject.hpp"
#include "Vertex.hpp"

class RendererBuffer {
    std::unique_ptr<VertexArrayObject> vao;
    GLuint vbo;
public:
    RendererBuffer(std::vector<Vertex> vertices);
    ~RendererBuffer();

    void bind() const;
};
