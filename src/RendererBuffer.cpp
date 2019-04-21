#include "RendererBuffer.hpp"
#include <stddef.h>
#include <iostream>
#include "Vertex.hpp"
#include "Texel.hpp"

using namespace std;

template <class T>
RendererBuffer<T>::RendererBuffer(uint capacity) : vao(make_unique<VertexArrayObject>()), capacity(capacity), size(0) {
    glGenBuffers(1, &vbo);

    vao->bind();
    bind();

    GLsizeiptr bufferSize = sizeof(T) * capacity;
    glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_DYNAMIC_DRAW);
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

template <class T>
void RendererBuffer<T>::addData(vector<T> data) {
    uint remainingCapacity = capacity - size;
    if (data.size() > remainingCapacity) {
        cout << "Renderer buffer out of memory." << endl;
        exit(1);
    }
    bind();

    uint offset = size * sizeof(T);
    uint dataSize = data.size() * sizeof(T);
    glBufferSubData(GL_ARRAY_BUFFER, offset, dataSize, data.data());

    size += data.size();
}

template <>
void RendererBuffer<Vertex>::enableAttributes() const {
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, color));
    glEnableVertexAttribArray(1);
}

template <>
void RendererBuffer<Texel>::enableAttributes() const {
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Texel), (void*)offsetof(struct Texel, position));
    glEnableVertexAttribArray(0);
}

template class RendererBuffer<Vertex>;
template class RendererBuffer<Texel>;
