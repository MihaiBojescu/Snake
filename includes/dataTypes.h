#ifndef DATATYPES_H
#define DATATYPES_H
#include <string>
#include <vector>

#ifndef GRID_SIZE
#define GRID_SIZE 12
#endif


class AI;
class snake;
class shader;
class point;
class textHelper;

class point
{
public:
    point();
    point(int x, int y);
    point(const point &newPoint);
    point operator+(const point &newPoint);
    point& operator=(const point &newPoint);
    bool operator==(const point &comparator);
    int x, y;
};

template <class T>
class queue
{
public:
    queue();
    ~queue();

    T operator[](const int index);

    void insertLast(T information);
    T* popFirst();

    unsigned getSize();
    bool isEmpty();

private:
    template <class Y>
    class innerQueue
    {
    public:
        innerQueue();
        ~innerQueue();

        Y info;
        innerQueue *next;
    };

    unsigned numberOfElements;
    innerQueue<T> *first;
    innerQueue<T> *last;
};

class binaryTree
{
public:
    binaryTree();
    ~binaryTree();

    void addNode(int info, std::string name);
    void buildQueue();
    std::vector<int> getIntVector();
    std::vector<std::string> getStringVector();

private:
    class treeNode
    {
    public:
        treeNode();
        ~treeNode();

        treeNode *left;
        treeNode * right;

        std::string name;
        int info;
    };
    std::vector<std::string> sortedListString;
    std::vector<int> sortedListInt;
    treeNode *root;

    void addNode(binaryTree::treeNode *&root, int info, std::string name);
    void buildQueue(binaryTree::treeNode *&root);
};

template class queue<int>;
template class queue<std::string>;
#endif
