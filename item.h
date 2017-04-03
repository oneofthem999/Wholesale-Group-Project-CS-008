#ifndef ITEM_H
#define ITEM_H
#include <string>

const double SALES_TAX_RATE = .0875;

class Item
{
    public:
        Item(std::string itemName = "", double itemPrice = 0.00, int itemQuantity = 1,
             double subtotal = 0.00, double tax = 0.00, double total = 0.00);
        std::string getItemName();
        double getItemPrice();
        int getItemQuantity();
        double getSubtotal();
        double getTax();
        double getTotal();

        void setItemName(std::string);
        void setItemPrice(double);
        void setItemQuantity(int);
        void setSubtotal();
        void setTax();
        void setTotal();

        bool operator>(const Item& RHS);

    private:
        std::string itemName;
        double itemPrice;
        int itemQuantity;
        double subtotal;
        double tax;
        double total;
};

#endif
