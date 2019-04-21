#include "RendererBuffer.hpp"
#include <stddef.h>
#include <Vertex.hpp>

using namespace std;

template <class T>
RendererBuffer<T>::RendererBuffer(vector<T> objects) : vao(make_unique<VertexArrayObject>()) {
    glGenBuffers(1, &vbo);

    vao->bind();
    bind();

    glBufferData(GL_ARRAY_BUFFER, sizeof(T) * objects.size(), objects.data(), GL_STATIC_DRAW);
    enableAttributes();
}

template <class T>
RendererBuffer<T>::~RendererBuffer() {
    glDeleteBuffers(1, &vbo);
}

template <class T>
void RendererBuffer<T>::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

template <>
void RendererBuffer<Vertex>::enableAttributes() const {
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, color));
    glEnableVertexAttribArray(1);
}

template class RendererBuffer<Vertex>;
