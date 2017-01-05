#ifndef SHADERS_H
#define SHADERS_H
#include "snake.h"
#include <string>
#include <GL/glew.h>

GLuint loadShaders(std::string vertexPath, std::string fragmentPath);
std::vector<GLfloat> generateVertexArray(std::vector<point> tail);
std::vector<GLfloat> generateVertexArray(std::vector<food> foodPieces);
std::vector<GLfloat> generateVertexArray(point head);
std::vector<GLfloat> generateColorArray(std::vector<food> foodPieces);
void initOpenGLData(GLuint &vertexBuffer, GLuint &colorBuffer, GLuint &vertexArrayID);
void refreshAndDraw(GLuint &program, GLuint &vertexBuffer, GLuint &colorBuffer, GLuint &vertexArrayObject, std::vector<GLfloat> vertexBufferVector, std::vector<GLfloat> colorBufferVector);
void cleanUp(GLuint &vertexBuffer, GLuint &colorBuffer, GLuint &vertexArrayID, GLuint &program);

#endif
