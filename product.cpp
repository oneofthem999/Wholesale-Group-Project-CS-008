#include "product.h"

Product::Product(string productName, double price, int quantity):productName(productName), price(price), quantity(quantity)
{
    setTotal();  //the subtotal and tax will also be set in the setTotal.
}
//accessors

void Product::setName(string name){
    productName = name;
}

void Product::setPrice(double p){
    price = p;
}

void Product::setQuantity(int q){
    quantity = q;
}

void Product::setSubtotal(){
    subtotal = price * quantity;
}

void Product::setTax(){
    tax = subtotal * SALES_TAX_RATE;
}

void Product::setTotal(){
    setSubtotal();
    setTax();
    total = subtotal + tax;
}

bool Product::operator>(const Product& RHS){
    return (productName > RHS.productName);
}

bool Product::operator<(const Product& RHS){
    return (productName < RHS.productName);
}

bool Product::operator>=(const Product& RHS){
    return (productName >= RHS.productName);
}

bool Product::operator<=(const Product& RHS){
    return (productName <= RHS.productName);
}

bool Product::operator==(const Product& RHS){
    return (productName == RHS.productName);
}

bool Product::operator!=(const Product& RHS){
    return (productName != RHS.productName);
}

