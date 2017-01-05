#ifndef SNAKE_H
#define SNAKE_H
#include "point.h"
#include "food.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <vector>

class snake
{
public:
    snake();
    ~snake();

    enum
    {
        ok = 0,
        hit = 1
    };

    void eat(int value);
    int move(point &direction, std::vector<food> &foodVector);
    int getSize();
    int getSpeed();
    unsigned getScore();
    std::vector<point> getTail();
    std::vector<GLfloat> getColors();
    point getHeadLocation();

private:
    std::vector<point> tail;
    std::vector<GLfloat> colors;
    point headLocation;
    unsigned score;
    unsigned speed;
    double timer;

    void processFood(food foodPiece);
    void increaseSpeed(int value);
    void grow(point location);
    void shrink();
};

#endif
