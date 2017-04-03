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

void Inventory::deleteFromInventory(const Item& itemToDelete)
{
    node<Item> *temp = search(itemToDelete);

    if (temp != inventory.begin())
        inventory.DeleteNode(temp);
    else
        inventory.DeleteHead();
}
