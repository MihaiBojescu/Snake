#include "../includes/game.h"
#include "../includes/snake.h"
#include "../includes/shaders.h"
#include <vector>
#ifdef DEBUG
#include <iostream>
#endif

game::game()
{
    snake newSnake;
    point direction = {0, 0};
    food foodPiece;
    this->snakes.push_back(newSnake);
    this->directions.push_back(direction);
    this->foodPieces.push_back(foodPiece);
    this->scores.push_back(newSnake.getScore());

    this->generateVertices();
    this->initData();
}

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
    food foodPiece;
    this->foodPieces.push_back(foodPiece);

    this->generateVertices();
    this->initData();
}

game::game(unsigned snakeNumber, unsigned foodPieces)
{
    for(unsigned i = 0; i < snakeNumber; i++)
    {
        snake Snake;
        point direction = {0, 0};
        this->snakes.push_back(Snake);
        this->directions.push_back(direction);
        this->scores.push_back(Snake.getScore());
    }
    for(unsigned i = 0; i < foodPieces; i++)
    {
        food foodPiece;
        this->foodPieces.push_back(foodPiece);
    }

    this->generateVertices();
    this->initData();
}

game::~game()
{
    this->snakes.clear();
    this->directions.clear();
    this->scores.clear();
    this->foodPieces.clear();
    cleanUp(this->vertexBuffer, this->vertexBufferIdentifier, this->program);
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
    //initOpenGLData(this->vertexBuffer, this->vertexBufferIdentifier, this->vertices);
    refreshAndDraw(this->program, this->vertexBuffer, this->vertices);
}

int game::gameLoop()
{
    if(this->snakes.empty()) return 1;
    if(this->foodPieces.empty()) this->generateFoodPiece();

    if(this->snakes[0].move(this->directions[0], this->foodPieces) == 1 && (directions[0].x + directions[0].y) != 0)
    {
        this->snakes.erase(this->snakes.begin());
    }
    else
    {
        this->scores[0] = this->snakes[0].getScore();
        this->generateVertices();
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

void game::initData()
{
	this->program = loadShaders("./src/glsl/snakeVertex.glsl", "./src/glsl/snakeFragment.glsl");
	initOpenGLData(this->vertexBuffer, this->vertexBufferIdentifier, this->vertices);
}
