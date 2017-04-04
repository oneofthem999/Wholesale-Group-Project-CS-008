#include "inventory.h"

using namespace std;

Inventory::Inventory()
{
    numberOfItemsInIventory = 0;
}

void Inventory::addToInventory(const Item& newItem)
{
    inventory.InsertHead(newItem);
    inventory.sort();
}

node<Item>* Inventory::search(const Item& itemComp)
{
    node<Item> *temp = inventory.begin();
    while (temp != NULL)
    {
        if (temp->item == itemComp)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

node<Item>* Inventory::search(const string name)
{
    for (node<Item> *temp = inventory.begin(); temp != NULL; temp = temp->next)
    {
        if (temp->item.getItemName() == name)
            return temp;
    }
    return NULL;
}

int Inventory::quantityOfItem(const string name) { return search(name)->item.getItemQuantity(); }

double Inventory::salesPriceOfItem(const string name) { return search(name)->item.getItemPrice(); }

void Inventory::deleteFromInventory(const Item& itemToDelete)
{
    node<Item> *temp = search(itemToDelete);

    if (temp != inventory.begin())
        inventory.DeleteNode(temp);
    else
        inventory.DeleteHead();
}

List<Item>& Inventory::getInventory() { return inventory; }
