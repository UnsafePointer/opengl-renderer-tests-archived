#pragma once
#include <glad/glad.h>
#include <memory>
#include <vector>
#include "VertexArrayObject.hpp"

class RendererBuffer {
    std::unique_ptr<VertexArrayObject> vao;
    GLuint vbo;
public:
    RendererBuffer(std::vector<float> vertices);
    ~RendererBuffer();

    void bind() const;
};
