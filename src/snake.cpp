#include "../includes/snake.h"
#include "../includes/point.h"
#include "../includes/food.h"
/*#include "point.cpp"
#include "food.cpp"*/
#include <ctime>
#ifdef DEBUG
#include <iostream>
#endif

snake::snake()
{
    this->headLocation = (point){5, 6};
    this->grow(0, (point){3, 6});
    this->grow(0, (point){4, 6});
    this->grow(0, (point){5, 6});
    this->speed = 100;
    this->score = 0;
    this->timer = std::clock();
}

snake::~snake()
{
}

void snake::eat(int value)
{
    this->grow(value, this->headLocation);
    if(value == 1) this->increaseSpeed(200);
    this->score++;
}

void snake::eat(food *foodPiece)
{
    this->grow(foodPiece->getValue(), this->headLocation);
    if(foodPiece->getValue() == 1) this->increaseSpeed(10);
    this->score++;
}

void snake::increaseSpeed(int value)
{
    if(this->speed + value > 99) this->speed += value;
    else this->speed = 100;
}

int snake::getSize()
{
    return this->tail.size();
}

int snake::getSpeed()
{
    return this->speed;
}

unsigned snake::getScore()
{
    return this->score;
}

int snake::move(point &direction, std::vector<food> &foodVector)
{
    if(std::clock() - this->timer >= CLOCKS_PER_SEC / this->speed)
    {
        this->timer = std::clock();
        #ifdef DEBUG
            std::cout<<"Snake moved to ("<<(this->headLocation + direction).x<<", "<<(this->headLocation + direction).y<<")\n";
        #endif
        if((this->headLocation + direction) == this->tail[this->tail.size() - 2])
        {
            #ifdef DEBUG
                std::cout<<"Snake wants to go back. Preventing this.\n";
            #endif
            direction.x = this->tail.back().x - this->tail[this->tail.size() - 2].x;
            direction.y = this->tail.back().y - this->tail[this->tail.size() - 2].y;
        }

        if(this->headLocation.x + direction.x > GRID_SIZE * 2)
            this->headLocation.x = -1;
        if(this->headLocation.x + direction.x < 0)
            this->headLocation.x = GRID_SIZE * 2;
        if(this->headLocation.y + direction.y > GRID_SIZE * 2)
            this->headLocation.y = -1;
        if(this->headLocation.y + direction.y < 0)
            this->headLocation.y = GRID_SIZE * 2;

        this->headLocation = this->headLocation + direction;
        for(std::vector<point>::iterator i = this->tail.begin() + 1; i != this->tail.end(); i++)
            if((*i).x == headLocation.x && (*i).y == headLocation.y) return this->hit;

        this->tail.erase(this->tail.begin());
        this->tail.push_back(headLocation);

        bool stop = false;
        for(std::vector<food>::iterator i = foodVector.begin(); i != foodVector.end() && stop == false; i++)
            if((*i).getLocation() == this->headLocation)
            {
                this->grow((*i).getValue(), (*i).getLocation());
                foodVector.erase(i);
                stop = true;
            }
    }
    return this->ok;
}

void snake::grow(int value, point location)
{
    this->tail.push_back(location);
    if(value == 1) this->increaseSpeed(10);
}

std::vector<point> snake::getTail()
{
    return this->tail;
}

point snake::getHeadLocation()
{
    return this->headLocation;
}
