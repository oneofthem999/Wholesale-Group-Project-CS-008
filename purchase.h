#ifndef PURCHASE_H
#define PURCHASE_H
#include <string>
#include "thelist.h"

const double SALES_TAX_RATE = .0875;

struct purchase
{
    std::string transactionDate;
    std::string itemName;
    double itemPrice;
    double itemQuantity;
    double subtotal;
    double tax;
    double total;
};

class memberPurchase
{
    public:
        memberPurchase();
        double addPurchase(std::string date, std::string item,
                         double price, double quantity);
        int size() const {return numberOfMemberPurchases;}

    private:
        List<purchase> purchases;
        int numberOfMemberPurchases;
};

class purchaseHistory
{
    friend class memberPurchase;
    public:
        purchaseHistory();
        bool insertMemberPurchases(memberPurchase newPurchases);
        int size() const {return numberOfTotalPurchases;}

    private:
        List<memberPurchase> totalPurchases;
        int numberOfTotalPurchases;
};

#endif // PURCHASE_H
