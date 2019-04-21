#include "RendererBuffer.hpp"

using namespace std;

RendererBuffer::RendererBuffer(vector<float> vertices) : vao(make_unique<VertexArrayObject>()) {
    glGenBuffers(1, &vbo);

    vao->bind();
    bind();

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
}

RendererBuffer::~RendererBuffer() {
    glDeleteBuffers(1, &vbo);
}

void RendererBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
