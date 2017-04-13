#include "inventory.h"

inventory::inventory()
{
    numberOfItemsInIventory = 0;
    totalValue = 0;
}

void inventory::addToInventory(const Product &addme){
    totalValue += addme.getPrice();
    node<Product>* found = search(addme.getName());
    if(found)
    {
        int quantity = found->item.getQuantity() + addme.getQuantity();
        found->item.setQuantity(quantity);
    }
    else
    {
        productList.Insert(addme);
        numberOfItemsInIventory++;
        productList.sort();
    }
}

void inventory::addToInventory(string productName, double price,int quantity){
    Product addme(productName,price,quantity);
    addToInventory(addme);
}

void inventory::deleteFromInventory(const Product& deleteMe){
    node<Product> *temp = search(deleteMe);
    productList.DeleteNode(temp);
}

void inventory::deleteFromInventory(const string name){
    node<Product> *temp = search(name);
    productList.DeleteNode(temp);
}

node<Product>* inventory::search(const Product& searchMe){
    node<Product> *temp = productList.begin();
    while (temp != NULL)
    {
        if (temp->item == searchMe)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

node<Product>* inventory::search(const string name){
    for (node<Product> *temp = productList.begin(); temp != NULL; temp = temp->next)
    {
        if (temp->item.getName() == name)
            return temp;
    }
    return NULL;
}

void inventory::print(){
    node<Product> *temp=productList.begin();
    while(temp){
        cout<<"name: "<<temp->item.getName()
           <<" | "<<temp->item.getQuantity()<<endl;
        temp=temp->next;
    }
    cout<<endl;
}
