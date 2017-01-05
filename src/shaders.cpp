#include "../includes/shaders.h"
#include "../includes/files.h"
#include <string>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glew.h>

#ifdef DEBUG_SHADERS
#include <iostream>
#endif

GLuint loadShaders(std::string vertexPath, std::string fragmentPath)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string vertex = "";
    std::string fragment = "";

    fragment = readWholeFile(fragmentPath);
    vertex = readWholeFile(vertexPath);
    const char *vertexSource = vertex.c_str();
    const char *fragmentSource = fragment.c_str();

    #ifdef DEBUG_SHADERS
        std::cout<<fragmentSource[0];
        std::cout<<vertexSource[0];
    #endif

    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    #ifdef DEBUG_SHADERS
        GLint status = GL_FALSE;
        int logLength = 0;
        GLchar *error;

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
        error = new GLchar[logLength];
        glGetShaderInfoLog(vertexShader, logLength, NULL, error);
        std::cout<<error<<"\n";
        delete error;

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
        error = new GLchar[logLength];
        glGetShaderInfoLog(fragmentShader, logLength, NULL, error);
        std::cout<<error<<"\n";
        delete error;

        glGetProgramiv(program, GL_LINK_STATUS, &status);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        error = new GLchar[logLength];
        glGetProgramInfoLog(program, logLength, NULL, error);
        std::cout<<error<<"\n";
        delete error;
    #endif

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}



std::vector<GLfloat> generateVertexArray(std::vector<point> tail)
{
    std::vector<GLfloat> floatArray;
    float aux = 0.001f;

    for(std::vector<point>::iterator i = tail.begin(); i != tail.end(); i++)
    {
        floatArray.push_back(-1.0f + (float)(*i).x/GRID_SIZE + aux);
        floatArray.push_back(1.0f - (float)(*i).y/GRID_SIZE - aux);
        floatArray.push_back(0.0f);
        floatArray.push_back(-1.0f + (float)(*i).x/GRID_SIZE + aux);
        floatArray.push_back(1.0f - (float)((*i).y + 1)/GRID_SIZE + aux);
        floatArray.push_back(0.0f);
        floatArray.push_back(-1.0f + (float)((*i).x + 1)/GRID_SIZE - aux);
        floatArray.push_back(1.0f - (float)((*i).y + 1)/GRID_SIZE + aux);
        floatArray.push_back(0.0f);


        floatArray.push_back(-1.0f + (float)(*i).x/GRID_SIZE + aux);
        floatArray.push_back(1.0f - (float)(*i).y/GRID_SIZE - aux);
        floatArray.push_back(0.0f);
        floatArray.push_back(-1.0f + (float)((*i).x + 1)/GRID_SIZE - aux);
        floatArray.push_back(1.0f - (float)((*i).y)/GRID_SIZE - aux);
        floatArray.push_back(0.0f);
        floatArray.push_back(-1.0f + (float)((*i).x + 1)/GRID_SIZE - aux);
        floatArray.push_back(1.0f - (float)((*i).y + 1)/GRID_SIZE + aux);
        floatArray.push_back(0.0f);
    }

    #ifdef DEBUG_SHADERS
        for(int i = 0; i < floatArray.size(); i++)
            std::cout<<floatArray[i]<<", ";
        std::cout<<"end\n";
    #endif

    return floatArray;
}

std::vector<GLfloat> generateVertexArray(std::vector<food> foodVector)
{
    std::vector<GLfloat> floatArray;
    float aux = 0.01f;

    for(std::vector<food>::iterator i = foodVector.begin(); i != foodVector.end(); i++)
    {
        floatArray.push_back(-1.0f + (float)(*i).getLocation().x/GRID_SIZE + aux);
        floatArray.push_back(1.0f - (float)(*i).getLocation().y/GRID_SIZE - aux);
        floatArray.push_back(0.0f);
        floatArray.push_back(-1.0f + (float)(*i).getLocation().x/GRID_SIZE + aux);
        floatArray.push_back(1.0f - (float)((*i).getLocation().y + 1)/GRID_SIZE + aux);
        floatArray.push_back(0.0f);
        floatArray.push_back(-1.0f + (float)((*i).getLocation().x + 1)/GRID_SIZE - aux);
        floatArray.push_back(1.0f - (float)((*i).getLocation().y + 1)/GRID_SIZE + aux);
        floatArray.push_back(0.0f);

        floatArray.push_back(-1.0f + (float)(*i).getLocation().x/GRID_SIZE + aux);
        floatArray.push_back(1.0f - (float)(*i).getLocation().y/GRID_SIZE - aux);
        floatArray.push_back(0.0f);
        floatArray.push_back(-1.0f + (float)((*i).getLocation().x + 1)/GRID_SIZE - aux);
        floatArray.push_back(1.0f - (float)((*i).getLocation().y)/GRID_SIZE - aux);
        floatArray.push_back(0.0f);
        floatArray.push_back(-1.0f + (float)((*i).getLocation().x + 1)/GRID_SIZE - aux);
        floatArray.push_back(1.0f - (float)((*i).getLocation().y + 1)/GRID_SIZE + aux);
        floatArray.push_back(0.0f);
    }

    #ifdef DEBUG_SHADERS
        for(int i = 0; i < floatArray.size(); i++)
            std::cout<<floatArray[i]<<", ";
        std::cout<<"end\n";
    #endif

    return floatArray;
}

std::vector<float> generateVertexArray(point head)
{
    std::vector<float> floatArray;
    float aux = 0.0f;

    floatArray.push_back(-1.0f + (float)head.x/GRID_SIZE + aux);
    floatArray.push_back(1.0f - (float)head.y/GRID_SIZE - aux);
    floatArray.push_back(0.0f);
    floatArray.push_back(-1.0f + (float)head.x/GRID_SIZE + aux);
    floatArray.push_back(1.0f - (float)(head.y + 1)/GRID_SIZE + aux);
    floatArray.push_back(0.0f);
    floatArray.push_back(-1.0f + (float)(head.x + 1)/GRID_SIZE - aux);
    floatArray.push_back(1.0f - (float)(head.y + 1)/GRID_SIZE + aux);
    floatArray.push_back(0.0f);

    floatArray.push_back(-1.0f + (float)head.x/GRID_SIZE + aux);
    floatArray.push_back(1.0f - (float)head.y/GRID_SIZE - aux);
    floatArray.push_back(0.0f);
    floatArray.push_back(-1.0f + (float)(head.x + 1)/GRID_SIZE - aux);
    floatArray.push_back(1.0f - (float)(head.y)/GRID_SIZE - aux);
    floatArray.push_back(0.0f);
    floatArray.push_back(-1.0f + (float)(head.x + 1)/GRID_SIZE - aux);
    floatArray.push_back(1.0f - (float)(head.y + 1)/GRID_SIZE + aux);
    floatArray.push_back(0.0f);

    #ifdef DEBUG_SHADERS
        for(int i = 0; i < floatArray.size(); i++)
            std::cout<<floatArray[i]<<", ";
        std::cout<<"end\n";
    #endif

    return floatArray;
}

void initOpenGLData(GLuint &vertexBuffer, GLuint &colorBuffer, GLuint &vertexArrayObject)
{
	glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &colorBuffer);
}

void refreshAndDraw(GLuint &program, GLuint &vertexBuffer, GLuint &colorBuffer, GLuint &vertexArrayObject, std::vector<GLfloat> vertexBufferVector, std::vector<GLfloat> colorBufferVector)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferVector.size() * sizeof(GLfloat), &vertexBufferVector[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colorBufferVector.size() * sizeof(GLfloat), &colorBufferVector[0], GL_DYNAMIC_DRAW);

    glBindVertexArray(vertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindVertexArray(0);

    glBindVertexArray(vertexArrayObject);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, vertexBufferVector.size() / 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void cleanUp(GLuint &vertexBuffer, GLuint &colorBuffer, GLuint &vertexArrayID, GLuint &program)
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteVertexArrays(1, &vertexArrayID);
    glDeleteProgram(program);
}
