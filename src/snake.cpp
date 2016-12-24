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
