#include "../includes/point.h"

point point::operator+(const point &newPoint)
{
    point returnPoint;
    returnPoint.x = this->x + newPoint.x;
    returnPoint.y = this->y + newPoint.y;
    return returnPoint;
}

void point::operator=(const point &newPoint)
{
    this->x = newPoint.x;
    this->y = newPoint.y;
}

bool point::operator==(const point &comparator)
{
    return ((this->x == comparator.x) && (this->y == comparator.y));
}
