#include "food.h"
#include "point.h"
#include <cstdlib>

food::food()
{
    this->value = rand() % 5;
    this->location.x = rand() % GRID_SIZE;
    this->location.y = rand() % GRID_SIZE;
}

food::food(unsigned value)
{
    this->value = value;
    this->location.x = rand() % GRID_SIZE;
    this->location.y = rand() % GRID_SIZE;
}

food::food(point location, unsigned value)
{
    this->value = value;
    this->location.x = location.x;
    this->location.y = location.y;
}

food::~food()
{
}

unsigned food::getValue()
{
    return this->value;
}

point food::getLocation()
{
    return this->location;
}
