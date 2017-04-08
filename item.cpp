#include "item.h"

using namespace std;

Item::Item(string name, double price, int quantity, double sTotal, double taxes, double trueTotal)
    : itemName(name), itemPrice(price), itemQuantity(quantity), subtotal(sTotal), tax(taxes), total(trueTotal)
{
    setTotal();
}

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

bool Item::operator<(const Item& RHS)
{
    return (this->itemName < RHS.itemName);
}

bool Item::operator>=(const Item& RHS)
{
    return (this->itemName >= RHS.itemName);
}

bool Item::operator<=(const Item& RHS)
{
    return (this->itemName < RHS.itemName);
}

bool Item::operator==(const Item& RHS)
{
    return (itemName == RHS.itemName);
}
bool Item::operator!=(const Item& RHS)
{
    return (itemName != RHS.itemName);
}
