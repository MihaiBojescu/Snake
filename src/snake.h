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

    enum
    {
        ok = 0,
        hit = 1
    };

    void eat(int value);
    int move(point headPoint);
    int getSize();
    point getHeadLocation();

private:
    std::vector<point> tail;
    point headLocation;

    void grow(int value, point location);
};

#endif
