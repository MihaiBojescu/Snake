#ifndef TEXT_H
#define TEXT_H
#include "shaders.h"
#include <string>
#include <map>
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

struct size
{
    int width;
    int height;
};

struct character
{
    ~character();
    GLuint texture;
    GLint width;
    GLint height;
    GLint left;
    GLint top;
    GLint advance;
};

class textHelper
{
public:
    textHelper(std::string fontPath, int height);
    ~textHelper();
    void renderTextAt(std::string text, GLfloat x, GLfloat y, GLfloat scale, GLfloat colors[3]);

private:
    FT_Library freetypeLibrary;
    FT_Face fontFace;

    GLuint texture;
    GLuint vertexBufferObject;
    GLuint vertexArrayObject;

    shader *shaderProgram;

    std::map<GLchar, character> Characters;
};
#endif
