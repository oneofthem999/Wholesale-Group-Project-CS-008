#ifndef PURCHASE_H
#define PURCHASE_H
#include <string>
#include "thelist.h"
<<<<<<< HEAD
#include "Item.h"
=======
#include "item.h"
>>>>>>> 0a42db703a0f5d93767bd7117a704ee57cec3a92

struct purchase
{
    std::string transactionDate;
    Item item;
<<<<<<< HEAD

    bool operator!=(const purchase& RHS);

    friend ostream& operator<<(ostream& out, purchase purch);

=======
    bool operator!=(const purchase& RHS);
    friend ostream& operator<<(ostream& out, purchase purch);
>>>>>>> 0a42db703a0f5d93767bd7117a704ee57cec3a92
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
<<<<<<< HEAD
    void insertMemberPurchases(memberPurchase newPurchases);
    bool isInList(memberPurchase mem);
=======
    bool isInList(memberPurchase mem);
    void insertMemberPurchases(memberPurchase newPurchases);
>>>>>>> 0a42db703a0f5d93767bd7117a704ee57cec3a92
    int size() const { return numberOfTotalPurchases; }

private:
    List<memberPurchase> totalPurchases;
    int numberOfTotalPurchases;
};

#endif // PURCHASE_H
