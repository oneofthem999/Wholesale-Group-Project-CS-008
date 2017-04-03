#ifndef INVENTORY_H
#define INVENTORY_H
#include "thelist.h"
#include "Item.h"

class Inventory
{
public:
    Inventory();
    void addToInventory(const Item&);
    node<Item>* search(const Item&);
    void deleteFromInventory(const Item&);
private:
    List<Item> inventory;
    int numberOfItemsInIventory;
};

#endif
