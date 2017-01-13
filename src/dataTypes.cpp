#include "../includes/dataTypes.h"
#include <iostream>
#include <cstddef> //explicitly for NULL, because I need it :)

point::point()
{
    this->x = 0;
    this->y = 0;
}

point::point(int x, int y)
{
    this->x = x;
    this->y = y;
}

point::point(const point &newPoint)
{
    this->x = newPoint.x;
    this->y = newPoint.y;
}

point point::operator+(const point &newPoint)
{
    point returnPoint;
    returnPoint.x = this->x + newPoint.x;
    returnPoint.y = this->y + newPoint.y;
    return returnPoint;
}

point& point::operator=(const point &newPoint)
{
    if(this == &newPoint)
        return *this;
    x = newPoint.x;
    y = newPoint.y;
    return *this;
}

bool point::operator==(const point &comparator)
{
    return ((this->x == comparator.x) && (this->y == comparator.y));
}

template <class T>
template <class Y>
queue<T>::innerQueue<Y>::innerQueue()
{
    this->next = NULL;
}

template <class T>
template <class Y>
queue<T>::innerQueue<Y>::~innerQueue()
{
    if(this->next) delete this->next;
    this->next = NULL;
}

template <class T>
queue<T>::queue()
{
    this->numberOfElements = 0;
    this->first = NULL;
    this->last = NULL;
}

template <class T>
queue<T>::~queue()
{
    if(this->first != NULL) delete this->first;
}

template <class T>
T queue<T>::operator[](const int index)
{
    if(index < 0) return 0;
    else if(index == this->numberOfElements) return this->last->info;
    else if(index > numberOfElements) return 0;

    queue<T>::innerQueue<T> *iterator = 0;
    int i = 0;
    for(i = 0, iterator = this->first; i < index; iterator = iterator->next, i++);

    return iterator->info;
}

template <class T>
void queue<T>::insertLast(T information)
{
    if(this->first == NULL)
    {
        this->first = new queue<T>::innerQueue<T>();
        this->first->info = information;
        this->first->next = NULL;
        this->last = this->first;
    }
    else
    {
        queue<T>::innerQueue<T> *newNode = new queue::innerQueue<T>();
        newNode->info = information;
        newNode->next = NULL;
        last->next = newNode;
        last = newNode;
    }
}

template <class T>
T* queue<T>::popFirst()
{
    if(this->numberOfElements == 0) return NULL;

    T *returnValue = &this->first->info;
    queue<T>::innerQueue<T> *nodeToBeDeleted = this->first;

    this->numberOfElements--;
    this->first = this->first->next;
    delete nodeToBeDeleted;
    return returnValue;
}

template <class T>
unsigned queue<T>::getSize()
{
    return this->numberOfElements;
}

template <class T>
bool queue<T>::isEmpty()
{
    return this->numberOfElements == 0;
}

binaryTree::treeNode::treeNode()
{
    this->left = NULL;
    this->right = NULL;
    this->info = 0;
    this->name = "";
}

binaryTree::treeNode::~treeNode()
{
    if(this->left) delete this->left;
    if(this->right) delete this->right;
    this->info = 0;
    this->name.clear();
}

binaryTree::binaryTree()
{
    this->root = NULL;
}

binaryTree::~binaryTree()
{
    this->sortedListString.clear();
    this->sortedListInt.clear();
    if(this->root) delete this->root;
}

void binaryTree::addNode(int info, std::string name)
{
    this->addNode(this->root, info, name);
}

void binaryTree::addNode(binaryTree::treeNode *&node, int info, std::string name)
{
    if(node == NULL)
    {
        node = new binaryTree::treeNode();
        node->info = info;
        node->name = name;
    }
    else
    {
        if(node->info < info) this->addNode(node->left, info, name);
        else this->addNode(node->right, info, name);
    }
}

void binaryTree::buildQueue()
{
    this->buildQueue(this->root);
}

void binaryTree::buildQueue(binaryTree::treeNode *&root)
{
    if(root == NULL) return;
    else
    {
        if(root->left) this->buildQueue(root->left);
        this->sortedListString.push_back(root->name);
        this->sortedListInt.push_back(root->info);
        if(root->right) this->buildQueue(root->right);
    }
}

std::vector<std::string> binaryTree::getStringVector()
{
    return this->sortedListString;
}

std::vector<int> binaryTree::getIntVector()
{
    return this->sortedListInt;
}
