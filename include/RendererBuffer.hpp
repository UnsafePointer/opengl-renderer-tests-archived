#pragma once
#include <glad/glad.h>
#include <memory>
#include <vector>
#include "VertexArrayObject.hpp"
#include "RendererProgram.hpp"
#include <cstdint>

template <class T>
class RendererBuffer {
    std::unique_ptr<VertexArrayObject> vao;
    GLuint vbo;
    std::unique_ptr<RendererProgram> &program;
    uint32_t capacity;
	uint32_t size;

    void enableAttributes() const;
public:
    RendererBuffer(std::unique_ptr<RendererProgram> &program, uint32_t capacity);
    ~RendererBuffer();

    void bind() const;
    void clean();
    void addData(std::vector<T> data);
    void draw();
};
