#ifndef SHADERS_H
#define SHADERS_H
#include "snake.h"
#include <string>
#include <GL/glew.h>

std::vector<GLfloat> generateVertexArray(std::vector<point> tail);
std::vector<GLfloat> generateVertexArray(std::vector<food> foodPieces);
std::vector<GLfloat> generateVertexArray(point head);
std::vector<GLfloat> generateColorArray(std::vector<food> foodPieces);

GLint getAttribute(GLuint program, std::string name);
GLint getUniform(GLuint program, std::string name);

class shader
{
public:
    shader(std::string vertexPath, std::string fragmentPath);
    ~shader();

    void useProgram();
    GLuint getProgram();

private:
    GLuint program;
};
#endif
