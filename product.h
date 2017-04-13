#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>

using namespace std;

const double SALES_TAX_RATE = 0.0875;

class Product
{
public:
    Product(std::string productName = "", double price = 0.00, int quantity = 1);
    //accessors
    std::string getName() const{return productName;}
    double getPrice() const{return price;}
    int getQuantity() const{return quantity;}
    double getSubtotal() const{return subtotal;}
    double getTax() const{return tax;}
    double getTotal() const{return total;}

    void setName(string name);
    void setPrice(double p);
    void setQuantity(int q);

    bool operator>(const Product& RHS);
    bool operator<(const Product& RHS);
    bool operator>=(const Product& RHS);
    bool operator<=(const Product& RHS);
    bool operator==(const Product& RHS);
    bool operator!=(const Product& RHS);
private:
    std::string productName;
    double price;
    int quantity;
    double subtotal;  //price*quantity (before tax
    double tax;
    double total;  //with tax

    void setTotal(); //once setTotal, the subtotal and tax will also be set.
    void setSubtotal();
    void setTax();
};

#endif // PRODUCT_H
