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

void Inventory::deleteFromInventory(const Item& itemToDelete)
{
//    List<Item>::Iterator iter = inventory.Search(itemToDelete);
//    inventory.DeleteNode(iter);
}
