#pragma once
#include <glad/glad.h>

class Vertex {
    GLfloat x, y;
    GLfloat r, g, b;
public:
    Vertex(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b);
    ~Vertex();
};
