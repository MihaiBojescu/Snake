#ifndef GAME_H
#define GAME_H
#include "snake.h"
#include <GLFW/glfw3.h>
#include <vector>

class game
{
public:
    game();
    game(unsigned snakeNumber);
    game(unsigned snakeNumber, unsigned foodPieces);
    ~game();

    void setDirection(point newDirection);
    void generateVertices();
    void generateFoodPiece();
    void generateFoodPiece(unsigned value);
    void drawGame();
    int gameLoop();
    std::vector<unsigned> getScores();
    std::vector<GLfloat> getVertices();
private:
    std::vector<GLfloat> vertices;
    std::vector<point> directions;
    std::vector<snake> snakes;
    std::vector<food> foodPieces;
    std::vector<unsigned> scores;

	GLuint vertexBufferIdentifier;
	GLuint vertexBuffer;
	GLuint program;

	void initData();
};

#endif
