#pragma once
#include <glad/glad.h>
#include <memory>
#include <vector>
#include "VertexArrayObject.hpp"

template <class T>
class RendererBuffer {
    std::unique_ptr<VertexArrayObject> vao;
    GLuint vbo;
    uint capacity;
    uint size;

    void enableAttributes() const;
public:
    RendererBuffer(uint capacity);
    ~RendererBuffer();

    void bind() const;
    void addData(std::vector<T> data);
};
