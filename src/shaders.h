#ifndef SHADERS_H
#define SHADERS_H
#include "snake.h"
#include <string>
#include <GL/glew.h>

GLuint loadShaders(std::string vertexPath, std::string fragmentPath);
std::vector<float> generateVertexArray(std::vector<point> tail);
std::vector<float> generateVertexArray(std::vector<food> tail);
std::vector<float> generateVertexArray(point head);
void initData(GLuint &vertexBuffer, GLuint &vertexArrayID, std::vector<GLfloat> buffer);
void refreshAndDraw(GLuint &program, GLuint &vertexBuffer, std::vector<GLfloat> buffer);
void cleanUp(GLuint &vertexBuffer, GLuint &vertexArrayID, GLuint &program);

#endif
