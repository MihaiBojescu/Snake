#ifndef MENUS_H
#define MENUS_H
#include "../includes/text.h"
#include <vector>
#include <string>

class menuItem
{
public:
    menuItem(std::string text, int fontSize, float scale);
    ~menuItem();

    void draw(float x, float y, float colors[3]);

private:
    textHelper *textPainter;
    std::string menuItemText;
    float scale;
};

class menuItemList
{
public:
    menuItemList();
    ~menuItemList();

    menuItem* operator[](const int index);

    void addNode(std::string text, int fontSize, float scale);
    void removeNode(const int index);
    void removeLastNode();
    unsigned size();

private:
    class linkedList
	{
    public:
        linkedList();
        ~linkedList();

        menuItem *node;
	    linkedList *next;
	};

    linkedList *root;
    unsigned numberOfItems;
};

class menu
{
public:
    menu(   float startX,
            float startY,
            float unselectedColors[3],
            float selectedColors[3]);
    ~menu();

    void addItem(std::string text);
    void draw();
    void selectItem(int counter);;
    void setDisabled(bool value);
    bool getDisabled();
    unsigned getSelectedItem();

private:
    bool disabled;
    int x;
    int y;
    unsigned numberOfItems;
    unsigned currentItem;
    float unselectedColors[3];
    float selectedColors[3];
    menuItem *title;
    menuItemList *items;
};
#endif
