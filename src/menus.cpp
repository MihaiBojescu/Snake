#include "../includes/menus.h"
#include "../includes/text.h"
#include <iostream>

menuItem::menuItem(std::string text, int fontSize, float scale)
{
    this->menuItemText = text;
    this->scale = scale;
    this->textPainter = new textHelper("/usr/share/fonts/TTF/DejaVuSans.ttf", fontSize);
}

menuItem::~menuItem()
{
    delete this->textPainter;
}

void menuItem::draw(float x, float y, float colors[3])
{
    this->textPainter->renderTextAt(this->menuItemText, x, y, this->scale, colors);
}

//----------------------------------------------------

menuItemList::linkedList::linkedList()
{
    this->node = NULL;
    this->next = NULL;
}

menuItemList::linkedList::~linkedList()
{
    delete this->node;
    delete this->next;
    this->next = NULL;
}

menuItemList::menuItemList()
{
    this->root = NULL;
    this->numberOfItems = 0;
}

menuItemList::~menuItemList()
{
    if(this->root != NULL) delete this->root;
}

menuItem* menuItemList::operator[](const int index)
{
    if(index < 0 || index > this->numberOfItems) return NULL;

    menuItemList::linkedList *iterator = NULL;
    int i = 0;
    for(i = 0, iterator = this->root; i < index && iterator; iterator = iterator->next, i++);

    return iterator->node;
}

void menuItemList::addNode(std::string text, int fontSize, float scale)
{
    if(this->root == NULL)
    {
        root = new menuItemList::linkedList();
        root->node = new menuItem(text, fontSize, scale);
        root->next = NULL;
    }
    else
    {
        menuItemList::linkedList *i = NULL;
        for(i = this->root; i->next; i = i->next);

        menuItemList::linkedList *aux = new menuItemList::linkedList();
        aux->node = new menuItem(text, fontSize, scale);
        aux->next = NULL;
        i->next = aux;
    }
    this->numberOfItems++;
}

void menuItemList::removeNode(const int index)
{
    menuItemList::linkedList *iterator = NULL;
    int i = 0;
    for(i = 0, iterator = this->root; i < index && iterator; iterator = iterator->next, i++);

    if(i != index) return;
    else delete iterator->node;
}

void menuItemList::removeLastNode()
{
    menuItemList::linkedList *iterator = NULL;

    for(iterator = this->root; iterator->next; iterator = iterator->next);

    delete iterator;
}

unsigned menuItemList::size()
{
    return this->numberOfItems;
}

//----------------------------------------------------

menu::menu( float startX,
            float startY,
            float unselectedColors[3],
            float selectedColors[3])
{
    this->title = NULL;
    this->items = new menuItemList();
    this->disabled = false;
    this->x = startX;
    this->y = startY;
    this->unselectedColors[0] = unselectedColors[0];
    this->unselectedColors[1] = unselectedColors[1];
    this->unselectedColors[2] = unselectedColors[2];
    this->selectedColors[0] = selectedColors[0];
    this->selectedColors[1] = selectedColors[1];
    this->selectedColors[2] = selectedColors[2];
    this->numberOfItems = 0;
    this->currentItem = 0;
}

menu::~menu()
{
    if(this->title) delete this->title;
    if(this->items) delete this->items;
}

void menu::addItem(std::string text)
{
    if(this->title == NULL)
    {
        this->title = new menuItem(text, 48, 1.0f);
    }
    else
    {
        this->items->addNode(text, 36, 1.0f);
        this->numberOfItems = this->items->size();
    }
}

void menu::draw()
{
    if(this->disabled == false)
    {
        if(this->title != NULL)
        {
            float currentY = this->y;
            this->title->draw(this->x, currentY, this->unselectedColors);

            if(this->numberOfItems > 0)
            {
                currentY -= 50;
                menuItem *aux = NULL;

                for(unsigned i = 0; i < this->numberOfItems; i++)
                {
                    if(i == this->currentItem)
                    {
                        aux = (*this->items)[i];
                        aux->draw(this->x, currentY, this->selectedColors);
                    }
                    else
                    {
                        aux = (*this->items)[i];
                        aux->draw(this->x, currentY, this->unselectedColors);
                    }
                    currentY -= 40;
                }
            }
        }
    }
}

void menu::selectItem(int counter)
{
    if(numberOfItems == 0) return;
    if(this->currentItem + counter > 0 && this->currentItem + counter < this->numberOfItems)
        this->currentItem += counter;
    else if(this->currentItem + counter < 0)
        this->currentItem = this->numberOfItems;
    else
        this->currentItem = 0;
}

void menu::setDisabled(bool value)
{
    this->disabled = value;
}


bool menu::getDisabled()
{
    return this->disabled;
}


unsigned menu::getSelectedItem()
{
    return this->currentItem;
}
