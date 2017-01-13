#include "../includes/game.h"
#include "../includes/snake.h"
#include "../includes/shaders.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#ifdef DEBUG
#include <iostream>
#endif

game::game(unsigned snakeNumber)
{
    for(unsigned i = 0; i < snakeNumber; i++)
    {
        snake newSnake;
        point direction = {0, 0};
        this->snakes.push_back(newSnake);
        this->directions.push_back(direction);
        this->scores.push_back(newSnake.getScore());
    }

    std::srand(std::clock());
    for(int i = rand() % 3 + 3; i > 0; i--)
    {
        food foodPiece;
        this->foodPieces.push_back(foodPiece);
    }

    this->generateVertices();
    this->generateColors();
    this->initGraphicsData();

    #ifdef DEBUG
        std::cout<<"colors: ";
        for(unsigned i = 0; i < this->colors.size(); i++)
        {
            if(i % 3 == 0) std::cout<<"\n"<<i / 3<<": ";
            std::cout<<this->colors[i]<<", ";
        }
        std::cout<<"\n";

        std::cout<<"vertices: ";
        for(unsigned i = 0; i < this->vertices.size(); i++)
        {
            if(i % 2 == 0) std::cout<<"\n"<<i / 2<<": ";
            std::cout<<this->vertices[i]<<", ";
        }
        std::cout<<"\n";
    #endif
}

game::~game()
{
    this->snakes.clear();
    this->directions.clear();
    this->scores.clear();
    this->foodPieces.clear();

    delete this->shaderProgram;

    glDeleteBuffers(1, &this->vertexBufferObject);
    glDeleteBuffers(1, &this->colorBufferObject);
    glDeleteVertexArrays(1, &this->vertexArrayObject);
}

void game::setDirection(point newDirection)
{
    this->directions[0].x = newDirection.x;
    this->directions[0].y = newDirection.y;
    #ifdef DEBUG
        std::cout<<this->directions[0].x<<"\n";
        std::cout<<this->directions[0].y<<"\n";
    #endif
}

void game::generateFoodPiece()
{
    food foodPiece;
    this->foodPieces.push_back(foodPiece);
}

void game::generateFoodPiece(unsigned value)
{
    food foodPiece(value);
    this->foodPieces.push_back(foodPiece);
}

void game::drawGame()
{
    this->shaderProgram->useProgram();

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), &this->vertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferObject);
    glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(GLfloat), &this->colors[0], GL_DYNAMIC_DRAW);

    glBindVertexArray(this->vertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferObject);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindVertexArray(0);

    glBindVertexArray(this->vertexArrayObject);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() / 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int game::gameLoop()
{
    if(this->snakes.empty()) return 1;
    if(this->foodPieces.empty()) this->generateFoodPiece();

    for(int i = 0; i < this->snakes.size(); i++)
    {
        if(this->snakes[i].move(this->directions[i], this->foodPieces) == 1 && (directions[i].x + directions[i].y) != 0)
        {
            this->snakes.erase(this->snakes.begin());
        }
        else
        {
            this->scores[i] = this->snakes[i].getScore();
            this->generateVertices();
            this->generateColors();
        }
    }
    return 0;
}

std::vector<unsigned> game::getScores()
{
    return this->scores;
}

std::vector<GLfloat> game::getVertices()
{
    return this->vertices;
}

std::vector<snake> game::getSnakes()
{
    return this->snakes;
}

std::vector<food> game::getFoods()
{
    return this->foodPieces;
}

void game::initGraphicsData()
{
    this->shaderProgram = new shader("./src/glsl/snakeVertex.glsl", "./src/glsl/snakeFragment.glsl");
	glGenVertexArrays(1, &this->vertexArrayObject);
    glGenBuffers(1, &this->vertexBufferObject);
	glGenBuffers(1, &this->colorBufferObject);
}

void game::generateVertices()
{
    std::vector<GLfloat> returnVector;
    std::vector<GLfloat> vertices;

    for(std::vector<snake>::iterator i = this->snakes.begin(); i != this->snakes.end(); i++)
    {
        vertices = generateVertexArray((*i).getTail());
        returnVector.insert(returnVector.end(), vertices.begin(), vertices.end());
        vertices.clear();
    }
    vertices = generateVertexArray(this->foodPieces);
    returnVector.insert(returnVector.end(), vertices.begin(), vertices.end());
    vertices.clear();

    this->vertices = returnVector;
}

void game::generateColors()
{
    std::vector<GLfloat> returnVector;
    std::vector<GLfloat> colors;

    for(std::vector<snake>::iterator i = this->snakes.begin(); i != this->snakes.end(); i++)
    {
        for(unsigned j = 0; j < (*i).getTail().size() * 6; j++)
        {
            colors = (*i).getColors();
            returnVector.insert(returnVector.end(), colors.begin(), colors.end());
            colors.clear();
        }
    }
    for(std::vector<food>::iterator i = this->foodPieces.begin(); i != this->foodPieces.end(); i++)
    {
        for(unsigned j = 0; j < 6; j++)
        {
            colors = (*i).getColors();
            returnVector.insert(returnVector.end(), colors.begin(), colors.end());
            colors.clear();
        }
    }
    this->colors = returnVector;
}
