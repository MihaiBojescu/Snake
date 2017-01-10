#include "../includes/AI.h"
#include "../includes/game.h"
#include "../includes/snake.h"
#include "../includes/food.h"
#include <vector>
#include <cstring>
#include <cstddef> //NULL needed. NULL found
#ifdef DEBUG_AI
#include <iostream>
#include <ctime>
#endif

#ifdef DEBUG_AI
double debugTimer = std::clock();
#endif

AI::AI()
{
    this->matrix = new int[GRID_SIZE * GRID_SIZE * 2];
    this->aiQueue = new queue();
}

AI::~AI()
{
    if(this->aiQueue != NULL) delete this->aiQueue;
    if(this->matrix != NULL) delete[] matrix;
}

void AI::updateMatrix(std::vector<snake> snakes, std::vector<food> foods)
{
    memset(this->matrix, 0, GRID_SIZE*GRID_SIZE*sizeof(int)*2);

    for(std::vector<snake>::iterator currentSnake = snakes.begin(); currentSnake != snakes.end(); currentSnake++)
    {
        std::vector<point> tail = (*currentSnake).getTail();
        for(int i = 0; i < tail.size(); i++)
            this->matrix[tail[i].x * GRID_SIZE + tail[i].y] = -1;
    }
    for(std::vector<food>::iterator currentFood = foods.begin(); currentFood != foods.end(); currentFood++)
            this->matrix[(*currentFood).getLocation().x * GRID_SIZE + (*currentFood).getLocation().y] = -2;

    #ifdef DEBUG_AI
        if(std::clock() - debugTimer >= CLOCKS_PER_SEC / 10)
        {
            debugTimer = std::clock();
            std::cout<<"AI matrix:\n";
            for(int i = 0; i < GRID_SIZE * 2; i++)
            {
                for(int j = 0; j < GRID_SIZE * 2; j++)
                    std::cout<<this->matrix[i * GRID_SIZE + j]<<", ";
                std::cout<<"\n";
            }
        }
    #endif
}

point* AI::goToDirection(point myLocation, std::vector<snake> snakes, std::vector<food> foods)
{
    return NULL;
}
