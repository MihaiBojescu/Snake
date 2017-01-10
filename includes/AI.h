#ifndef AI_H
#define AI_H
#include "dataTypes.h"
#include "game.h"
#include "snake.h"
#include "food.h"
#include <vector>

class AI
{
public:
    AI();
    ~AI();

    point* goToDirection(point myLocation, std::vector<snake> snakes, std::vector<food> foods);

private:
    int *matrix;
    point myLocation;
    point lastDirection;
    queue *aiQueue;

    void updateMatrix(std::vector<snake> snakes, std::vector<food> foods);
};


#endif
