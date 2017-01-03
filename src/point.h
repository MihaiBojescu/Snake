#ifndef POINT_H
#define POINT_H

#ifndef GRID_SIZE
#define GRID_SIZE 12
#endif

class point
{
public:
    point operator+(const point &newPoint);
    void operator=(const point &newPoint);
    bool operator==(const point &comparator);
    int x, y;
};

#endif
