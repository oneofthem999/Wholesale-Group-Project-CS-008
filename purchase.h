#ifndef PURCHASE_H
#define PURCHASE_H
#include <string>
#include "thelist.h"
#include "Item.h"

struct purchase
{
    std::string transactionDate;
    Item item;

    bool operator!=(const purchase& RHS);

    friend ostream& operator<<(ostream& out, purchase purch);

};

class memberPurchase
{
public:
    memberPurchase();
    double addPurchase(std::string date, Item item);
    int size() const { return numberOfMemberPurchases; }
    node<purchase>* search(Item item);
    node<purchase>* search(std::string transactionDate);

    double totalPurchaseCostOnDate(std::string transactionDate);
    double totalPurchaseCost();
    List<purchase>& getPurchases();

    friend ostream& operator<<(ostream &out, List<purchase> purch);

private:
    List<purchase> purchases;
    int numberOfMemberPurchases;
};

class purchaseHistory
{
    friend class memberPurchase;
public:
    purchaseHistory();
    void insertMemberPurchases(memberPurchase newPurchases);
    bool isInList(memberPurchase mem);
    int size() const { return numberOfTotalPurchases; }

private:
    List<memberPurchase> totalPurchases;
    int numberOfTotalPurchases;
};

#endif // PURCHASE_H
