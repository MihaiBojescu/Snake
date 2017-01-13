#ifndef GAME_H
#define GAME_H
#include "snake.h"
#include "shaders.h"
#include <GLFW/glfw3.h>
#include <vector>

class game
{
public:
    game(unsigned snakeNumber);
    ~game();

    void setDirection(point newDirection);
    void generateFoodPiece();
    void generateFoodPiece(unsigned value);
    void drawGame();
    int gameLoop();
    std::vector<unsigned> getScores();
    std::vector<GLfloat> getVertices();
    std::vector<snake> getSnakes();
    std::vector<food> getFoods();

private:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;
    std::vector<point> directions;
    std::vector<snake> snakes;
    std::vector<food> foodPieces;
    std::vector<unsigned> scores;

    shader *shaderProgram;

    GLuint vertexArrayObject;
    GLuint vertexBufferObject;
    GLuint colorBufferObject;

    void initGraphicsData();
    void generateVertices();
    void generateColors();
};

#endif
