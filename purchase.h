#ifndef PURCHASE_H
#define PURCHASE_H
#include <string>
#include "thelist.h"
#include "Item.h"

struct purchase
{
    std::string transactionDate;
    Item item;
};

class memberPurchase
{
public:
    memberPurchase();
    double addPurchase(std::string date, Item item);
    int size() const { return numberOfMemberPurchases; }

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
    int size() const { return numberOfTotalPurchases; }

private:
    List<memberPurchase> totalPurchases;
    int numberOfTotalPurchases;
};

#endif // PURCHASE_H
