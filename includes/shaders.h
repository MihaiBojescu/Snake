#ifndef SHADERS_H
#define SHADERS_H
#include "../includes/snake.h"
#include <string>
#include <GL/glew.h>

extern GLuint loadShaders(std::string vertexPath, std::string fragmentPath);
extern std::vector<float> generateVertexArray(std::vector<point> tail);
extern std::vector<float> generateVertexArray(std::vector<food> tail);
extern std::vector<float> generateVertexArray(point head);
extern void initOpenGLData(GLuint &vertexBuffer, GLuint &vertexArrayID, std::vector<GLfloat> buffer);
extern void refreshAndDraw(GLuint &program, GLuint &vertexBuffer, std::vector<GLfloat> buffer);
extern void cleanUp(GLuint &vertexBuffer, GLuint &vertexArrayID, GLuint &program);

#endif
