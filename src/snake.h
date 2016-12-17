#ifndef SNAKE_H
#define SNAKE_H
#include <vector>

struct point
{
    int x, y;
};

class snake
{
public:
    snake();
    ~snake();

    void eat(int value);
    int getSize();

private:
    std::vector<point> tail;
    point headLocation;

    void grow(int value, point location);
};

#endif
