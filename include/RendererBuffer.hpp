#pragma once
#include <glad/glad.h>
#include <memory>
#include <vector>
#include "VertexArrayObject.hpp"

template <class T>
class RendererBuffer {
    std::unique_ptr<VertexArrayObject> vao;
    GLuint vbo;

    void enableAttributes() const;
public:
    RendererBuffer(std::vector<T> objects);
    ~RendererBuffer();

    void bind() const;
};
