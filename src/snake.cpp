#include "snake.h"

void snake::eat(int value)
{
    this->grow(value, this->headLocation);
}

int snake::getSize()
{
    return this->tail.size();
}

int snake::move(point newHeadLocation)
{
    for(std::vector<point>::iterator i = this->tail.begin() + 1; i != this->tail.end(); i++)
        if((*i).x == newHeadLocation.x && (*i).y == newHeadLocation.y) return this->hit;

    this->tail.erase(this->tail.begin());
    this->tail.push_back(newHeadLocation);
    return this->ok;
}

void snake::grow(int value, point location)
{
    this->tail.push_back(location);
}

point snake::getHeadLocation()
{
    return this->headLocation;
}
