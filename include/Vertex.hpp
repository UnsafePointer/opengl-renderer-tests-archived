#pragma once
#include <glad/glad.h>

struct Point {
    GLfloat x, y;
};

struct Color {
    GLfloat r, g, b;
};

struct Vertex {
    Point position;
    Color color;
public:
    Vertex(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b);
    ~Vertex();
};
