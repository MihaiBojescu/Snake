#ifndef SNAKE_H
#define SNAKE_H
#include "point.h"
#include "food.h"
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
    void eat(food *foodPiece);
    void increaseSpeed(int value);
    int move(point &direction, std::vector<food> &foodVector);
    int getSize();
    int getSpeed();
    unsigned getScore();
    std::vector<point> getTail();
    point getHeadLocation();

private:
    std::vector<point> tail;
    point headLocation;
    unsigned score;
    unsigned speed;
    double timer;

    void grow(int value, point location);
};

#endif
