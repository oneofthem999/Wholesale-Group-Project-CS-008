#ifndef INVENTORY_H
#define INVENTORY_H

#include "thelist.h"
#include "product.h"

class inventory          //a list of product
{
public:
    inventory();

    int getNumberOfItems(){return numberOfItemsInIventory;}
    double getTotalValue(){return totalValue;}
    List<Product>& getInventory();//?

    void addToInventory(const Product &addme);
    //***always add to inventory through name and quantity
    void addToInventory(string productName, double price,int quantity);
    void deleteFromInventory(const Product& deleteMe);
    void deleteFromInventory(const string name);

    node<Product>* search(const Product& searchMe);
    node<Product>* search(const string name);
//    bool isInInventory(const Product& searchMe);
//    bool isInInventory(const string name);

    //int quantityOfItem(const string name);
    //double salesPriceOfItem(const string name);
    void print();

private:
    List<Product> productList;
    int numberOfItemsInIventory;
    double totalValue;

    //sort
};

#endif // INVENTORY_H
