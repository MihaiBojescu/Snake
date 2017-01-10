#ifndef DATATYPES_H
#define DATATYPES_H

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

class queue
{
public:
    queue();
    ~queue();

    point* operator[](const int index);

    void insertLast(point information);
    point* popFirst();

    unsigned getSize();
    bool isEmpty();

private:
    class innerQueue
    {
    public:
        innerQueue();
        ~innerQueue();

        point info;
        innerQueue *next;
    };

    unsigned numberOfElements;
    innerQueue *first;
    innerQueue *last;
};

#endif
