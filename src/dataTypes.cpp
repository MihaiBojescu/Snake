#include "../includes/dataTypes.h"
#include <cstddef> //explicitly for NULL, because I need it :)

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

queue::innerQueue::innerQueue()
{
    this->info = (point){0, 0};
    this->next = NULL;
}

queue::innerQueue::~innerQueue()
{
    if(this->next) delete this->next;
    this->next = NULL;
}

queue::queue()
{
    this->numberOfElements = 0;
    this->first = NULL;
    this->last = NULL;
}

queue::~queue()
{
    if(this->first != NULL) delete this->first;
}

point* queue::operator[](const int index)
{
    if(index < 0) return NULL;
    else if(index == this->numberOfElements) return &this->last->info;
    else if(index > numberOfElements) return NULL;

    queue::innerQueue *iterator = NULL;
    int i = 0;
    for(i = 0, iterator = this->first; i < index; iterator = iterator->next, i++);

    return &iterator->info;
}

void queue::insertLast(point information)
{
    if(this->first == NULL)
    {
        this->first = new queue::innerQueue();
        this->first->info = information;
        this->first->next = NULL;
        this->last = this->first;
    }
    else
    {
        queue::innerQueue *newNode = new queue::innerQueue();
        newNode->info = information;
        newNode->next = NULL;
        last->next = newNode;
        last = newNode;
    }
}

point* queue::popFirst()
{
    if(this->numberOfElements == 0) return NULL;

    point *returnValue = &this->first->info;
    queue::innerQueue *nodeToBeDeleted = this->first;

    this->numberOfElements--;
    this->first = this->first->next;
    delete nodeToBeDeleted;
    return returnValue;
}

unsigned queue::getSize()
{
    return this->numberOfElements;
}

bool queue::isEmpty()
{
    return this->numberOfElements == 0;
}
