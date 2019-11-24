#pragma once
#include <glad/glad.h>
#include <string>
#include <vector>

class RendererProgram {
    GLuint program;

    std::string openShaderSource(std::string filePath);
    GLuint compileShader(std::string filePath, GLenum shaderType);
    GLuint linkProgram(std::vector<GLuint> shaders);
public:
    RendererProgram(std::string vertexShaderSrcPath, std::string fragmentShaderSrcPath);
    ~RendererProgram();

    void useProgram();
    GLuint findProgramAttribute(std::string attribute);
};
