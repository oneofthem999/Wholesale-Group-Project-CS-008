#ifndef INVENTORY_H
#define INVENTORY_H
#include "thelist.h"
#include "item.h"

class Inventory
{
public:
    Inventory();
    void addToInventory(const Item&);
    node<Item>* search(const Item&);
    node<Item>* search(const string name);
    int getNumberOfItems(){return numberOfItemsInIventory;}
    int quantityOfItem(const string name);
    double salesPriceOfItem(const string name);
    void deleteFromInventory(const Item&);
    List<Item>& getInventory();
    double getTotalValue();
private:
    List<Item> inventory;
    int numberOfItemsInIventory;
    double totalValue;
};

#endif
