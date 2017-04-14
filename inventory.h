#ifndef INVENTORY_H
#define INVENTORY_H
#include "thelist.h"
#include "product.h"

class Inventory
{
public:
    Inventory();
    void addToInventory(const Product &addme);
    //***always add to inventory through name and quantity
    void addToInventory(string productName, double price,int quantity);
    void deleteFromInventory(const Product& deleteMe);
    void deleteFromInventory(const string name);
    node<Product>* search(const Product& searchMe);
    node<Product>* search(const string name);
    int getNumberOfItems(){return numberOfItemsInIventory;}
    double getTotalValue(){return totalValue;}
    int quantityOfItem(const string name);
    double salesPriceOfItem(const string name);
    List<Product>& getInventory(){return inventory;}

private:
    List<Product> inventory;
    int numberOfItemsInIventory;
    double totalValue;
};

#endif
