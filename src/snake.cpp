#include "../includes/snake.h"
#include "../includes/dataTypes.h"
#include "../includes/food.h"
#include <ctime>
#include <cstdlib>
#ifdef DEBUG
#include <iostream>
#endif

snake::snake()
{
    std::srand(std::clock());
    this->headLocation = (point){rand() % (GRID_SIZE - 6) + 3, rand() % (GRID_SIZE - 6) + 3};
    this->grow((point){this->headLocation.x - 2, this->headLocation.y});
    this->grow((point){this->headLocation.x - 1, this->headLocation.y});
    this->grow((point){this->headLocation.x, this->headLocation.y});
    this->speed = 50;
    this->score = 0;
    this->timer = std::clock();

    srand(clock());
    this->colors.push_back((float)(rand() % 1000) / 1000);
    this->colors.push_back((float)(rand() % 1000) / 1000);
    this->colors.push_back((float)(rand() % 1000) / 1000);

    #ifdef DEBUG
        std::cout<<"Snake colors: ";
        for(std::vector<GLfloat>::iterator i = this->colors.begin(); i != this->colors.end(); i++)
        {
            std::cout<<(*i)<<", ";
        }
        std::cout<<"\n";
    #endif
}

snake::~snake()
{
    this->tail.clear();
    this->colors.clear();
}

void snake::eat(int value)
{
    this->grow(this->headLocation);
    if(value == 1) this->increaseSpeed(10);
    if(value == 2) this->increaseSpeed(-10);
    this->score++;
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

std::vector<point> snake::getTail()
{
    return this->tail;
}

std::vector<GLfloat> snake::getColors()
{
    return this->colors;
}

point snake::getHeadLocation()
{
    return this->headLocation;
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
           //     std::cout<<"Snake wants to go back. Preventing this.\n";
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
                this->processFood(*i);
                foodVector.erase(i);
                stop = true;
            }
    }
    return this->ok;
}


void snake::processFood(food foodPiece)
{
    switch(foodPiece.getValue())
    {
        case 0:
            this->grow();
            this->score++;
            break;

        case 1:
            this->grow();
            this->increaseSpeed(1);
            this->score++;
            break;

        case 2:
            this->grow();
            this->increaseSpeed(-1);
            this->score++;
            break;

        case 3:
            this->increaseSpeed(-10);
            this->shrink();
            this->score > 0 ? this->score-- : this->score;
            break;

        default:
            this->grow();
    }
}

void snake::increaseSpeed(int value)
{
    if(this->speed + value > 49) this->speed += value;
    else this->speed = 50;
}

void snake::grow(point location)
{
    this->tail.push_back(location);
}

void snake::grow()
{
    this->tail.insert(this->tail.begin(), this->tail.front());
}

void snake::shrink()
{
    if(this->tail.size() > 1)
        this->tail.erase(this->tail.begin());
}
