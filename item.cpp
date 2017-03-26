#include "Item.h"

using namespace std;

Item::Item(string name, double price, int quantity, double sTotal, double taxes, double trueTotal)
    : itemName(name), itemPrice(price), itemQuantity(quantity), subtotal(sTotal), tax(taxes), total(trueTotal)
{

}

std::string Item::getItemName() { return itemName; }

double Item::getItemPrice() { return itemPrice; }

int Item::getItemQuantity() { return itemQuantity; }

double Item::getSubtotal() { return subtotal; }

double Item::getTax() { return tax; }

double Item::getTotal() {return total; }

void Item::setItemName(std::string name) { itemName = name; }

void Item::setItemPrice(double price)
{
    itemPrice = price;
    setTotal();
}

void Item::setItemQuantity(int quantity)
{
    itemQuantity = quantity;
    setTotal();
}

void Item::setSubtotal()
{
    subtotal = getItemPrice() * getItemQuantity();
}

void Item::setTax()
{
    tax = getSubtotal() * SALES_TAX_RATE;
}

void Item::setTotal()
{
    setSubtotal();
    setTax();
    total = subtotal + tax;
}

bool Item::operator>(const Item& RHS)
{
    return (this->itemName > RHS.itemName);
}
