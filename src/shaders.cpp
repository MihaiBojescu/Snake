#include "../includes/shaders.h"
#include "../includes/files.h"
#include <string>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glew.h>
#include <iostream>

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

GLint getAttribute(GLuint program, std::string name)
{
	GLint attribute = glGetAttribLocation(program, name.c_str());
	if(attribute != -1)
	    return attribute;
	else
	    std::cout<<"Can't get attribute "<<name<<"\n";
}

GLint getUniform(GLuint program, std::string name)
{
	GLint uniform = glGetUniformLocation(program, name.c_str());
	if(uniform != -1)
	    return uniform;
	else
	    std::cout<<"Can't get uniform "<<name<<"\n";
}

shader::shader(std::string vertexPath, std::string fragmentPath)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string vertex = "";
    std::string fragment = "";

    vertex = readWholeFile(vertexPath);
    fragment = readWholeFile(fragmentPath);
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

    this->program = glCreateProgram();
    glAttachShader(this->program, vertexShader);
    glAttachShader(this->program, fragmentShader);
    glLinkProgram(this->program);

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

        glGetProgramiv(this->program, GL_LINK_STATUS, &status);
        glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &logLength);
        error = new GLchar[logLength];
        glGetProgramInfoLog(this->program, logLength, NULL, error);
        std::cout<<error<<"\n";
        delete error;
    #endif

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

shader::~shader()
{
    glDeleteProgram(this->program);
}

void shader::useProgram()
{
    glUseProgram(this->program);
}

GLuint shader::getProgram()
{
    return this->program;
}
