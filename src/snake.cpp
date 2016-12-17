#include "snake.h"

void snake::eat(int value)
{
    this->grow(value, this->headLocation);
}

int snake::getSize()
{
    return this->tail.size();
}

void snake::grow(int value, point location)
{
    this->tail.push_back(location);
}
