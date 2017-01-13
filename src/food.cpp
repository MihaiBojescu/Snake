#include "../includes/food.h"
#include "../includes/dataTypes.h"
#include <ctime>
#include <cstdlib>
#ifdef DEBUG
#include <iostream>
#endif

food::food()
{
    srand(std::clock());
    this->value = rand() % 4;
    this->generateColor();
    #ifdef DEBUG
        std::cout<<"Food colors: ";
        for(std::vector<GLfloat>::iterator i = this->colors.begin(); i != this->colors.end(); i++)
        {
            std::cout<<(*i)<<", ";
        }
        std::cout<<"\n";
    #endif
    this->location.x = rand() % (GRID_SIZE * 2);
    this->location.y = rand() % (GRID_SIZE * 2);
}

food::food(unsigned value)
{
    srand(std::clock());
    this->value = value;
    this->generateColor();
    this->location.x = rand() % (GRID_SIZE * 2);
    this->location.y = rand() % (GRID_SIZE * 2);
}

food::food(point location, unsigned value)
{
    this->value = value;
    this->generateColor();
    this->location.x = location.x;
    this->location.y = location.y;
}

food::~food()
{
    this->colors.clear();
}

unsigned food::getValue()
{
    return this->value;
}

point food::getLocation()
{
    return this->location;
}

std::vector<GLfloat> food::getColors()
{
    return this->colors;
}

void food::generateColor()
{
    switch(this->value)
    {
        case 0:
            this->colors.push_back(0.000f);
            this->colors.push_back(0.502f);
            this->colors.push_back(0.000f);
            break;

        case 1:
            this->colors.push_back(1.000f);
            this->colors.push_back(0.843f);
            this->colors.push_back(0.000f);
            break;

        case 2:
            this->colors.push_back(0.502f);
            this->colors.push_back(0.502f);
            this->colors.push_back(0.000f);
            break;

        case 3:
            this->colors.push_back(0.500f);
            this->colors.push_back(0.702f);
            this->colors.push_back(0.200f);
            break;

        default:
            this->colors.push_back(1.000f);
            this->colors.push_back(1.000f);
            this->colors.push_back(1.000f);
    }
}

