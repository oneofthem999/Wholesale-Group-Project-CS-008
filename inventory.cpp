#include "inventory.h"
#include <QDebug>
using namespace std;

Inventory::Inventory()
{
    numberOfItemsInIventory = 0;
    totalValue = 0;
}

void Inventory::addToInventory(const Product &newItem)
{
    node<Product>* found = search(newItem.getName());
    if(found)
    {
        int quantity = found->item.getQuantity() + newItem.getQuantity();
        found->item.setQuantity(quantity);
        totalValue += (newItem.getPrice() * newItem.getQuantity());

    }
    else
    {
        inventory.InsertHead(newItem);
        ++numberOfItemsInIventory;
        totalValue += (newItem.getPrice() * newItem.getQuantity());
        inventory.sort();
    }
}

void Inventory::addToInventory(string productName, double price, int quantity){
    Product addme(productName,price,quantity);
    addToInventory(addme);
}

void Inventory::deleteFromInventory(const Product &itemToDelete)
{
    node<Product> *temp = search(itemToDelete);

    if (temp != inventory.begin())
        inventory.DeleteNode(temp);
    else
        inventory.DeleteHead();
}

void Inventory::deleteFromInventory(const string name){
    node<Product> *temp = search(name);
    inventory.DeleteNode(temp);
}

node<Product> *Inventory::search(const Product& searchMe)
{
    node<Product> *temp = inventory.begin();
    while (temp != NULL)
    {
        if (temp->item == searchMe)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

node<Product> *Inventory::search(const string name)
{
    for (node<Product> *temp = inventory.begin(); temp != NULL; temp = temp->next)
    {
        if (temp->item.getName() == name)
            return temp;
    }
    return NULL;
}

int Inventory::quantityOfItem(const string name) { return search(name)->item.getQuantity(); }

double Inventory::salesPriceOfItem(const string name) { return search(name)->item.getPrice(); }

