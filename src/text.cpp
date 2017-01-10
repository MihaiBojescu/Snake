#include "../includes/text.h"
#include "../includes/shaders.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

character::~character()
{
    glDeleteBuffers(1, &this->texture);
}

textHelper::textHelper(std::string fontPath, int height)
{
    this->shaderProgram = new shader("./src/glsl/textVertex.glsl", "./src/glsl/textFragment.glsl");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(800));

    shaderProgram->useProgram();
    GLint projectionUniform = getUniform(this->shaderProgram->getProgram(), "projection");
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));

    FT_Init_FreeType(&this->freetypeLibrary);
    FT_New_Face(this->freetypeLibrary, fontPath.c_str(), 0, &this->fontFace);
    FT_Set_Pixel_Sizes(this->fontFace, 0, height);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(GLubyte i = 0; i < 128; i++)
    {
        if(FT_Load_Char(this->fontFace, i, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            this->fontFace->glyph->bitmap.width,
            this->fontFace->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            this->fontFace->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        character newCharacter;
        newCharacter.texture = texture;
        newCharacter.width = (GLint)this->fontFace->glyph->bitmap.width;
        newCharacter.height = (GLint)this->fontFace->glyph->bitmap.rows;
        newCharacter.left = (GLint)this->fontFace->glyph->bitmap_left;
        newCharacter.top = (GLint)this->fontFace->glyph->bitmap_top;
        newCharacter.advance = (GLint)this->fontFace->glyph->advance.x;

        this->Characters.insert(std::pair<GLchar, character>(i, newCharacter));
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(this->fontFace);
    FT_Done_FreeType(this->freetypeLibrary);

    glGenVertexArrays(1, &this->vertexArrayObject);
    glGenBuffers(1, &this->vertexBufferObject);
    glBindVertexArray(this->vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

textHelper::~textHelper()
{
    delete this->shaderProgram;

    glDeleteTextures(1, &this->texture);
    glDeleteBuffers(1, &this->vertexBufferObject);
    glDeleteVertexArrays(1, &this->vertexArrayObject);
}

void textHelper::renderTextAt(std::string text, GLfloat x, GLfloat y, GLfloat scale, GLfloat colors[3])
{
    this->shaderProgram->useProgram();
    GLint color = getUniform(this->shaderProgram->getProgram(), "textColor");
    glUniform3f(color, colors[0], colors[1], colors[2]);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->vertexArrayObject);

    for(std::string::const_iterator i = text.begin(); i != text.end(); i++)
    {
        character currentCharacter = this->Characters[*i];

        GLfloat positionX = x + currentCharacter.left * scale;
        GLfloat positionY = y - (currentCharacter.height - currentCharacter.top) * scale;

        GLfloat width = currentCharacter.width * scale;
        GLfloat height = currentCharacter.height * scale;

        GLfloat vertices[6][4] = {
            {positionX,         positionY + height, 0.0f, 0.0f},
            {positionX,         positionY,          0.0f, 1.0f},
            {positionX + width, positionY,          1.0f, 1.0f},
            {positionX,         positionY + height, 0.0f, 0.0f},
            {positionX + width, positionY,          1.0f, 1.0f},
            {positionX + width, positionY + height, 1.0f, 0.0f}
        };

        glBindTexture(GL_TEXTURE_2D, currentCharacter.texture);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (currentCharacter.advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
