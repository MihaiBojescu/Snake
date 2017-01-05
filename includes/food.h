#ifndef FOOD_H
#define FOOD_H
#include "point.h"
#include <vector>
#include <GL/glew.h>

class food
{
public:
    food();
    food(unsigned value);
    food(point location, unsigned value);
    ~food();

    unsigned getValue();
    point getLocation();
    std::vector<GLfloat> getColors();
private:
    std::vector<GLfloat> colors;
    point location;
    unsigned value;

    void generateColor();
};

#endif
