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
    node<Item>* search(const string name);
    int quantityOfItem(const string name);
    double salesPriceOfItem(const string name);
    void deleteFromInventory(const Item&);
    List<Item>& getInventory();

private:
    List<Item> inventory;
    int numberOfItemsInIventory;
};

#endif
