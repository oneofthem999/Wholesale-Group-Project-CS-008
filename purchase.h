#ifndef PURCHASE_H
#define PURCHASE_H
#include <string>
#include "thelist.h"
#include "product.h"

struct purchase
{
    std::string transactionDate;
    Product product;
    bool operator!=(const purchase& RHS);
    bool operator>(const purchase& RHS);
    friend ostream& operator<<(ostream& out, purchase& purch);
};

class memberPurchase
{
public:
    // constructors
    memberPurchase();
    memberPurchase(std::string id);
    // mutators
    void addPurchase(std::string date, Product& item);
    void changeID(std::string id);
    // accessors
    node<purchase>* search(Product& item);
    node<purchase>* search(string transactionDate, int& pos, bool& finish);
    node<purchase>* search(std::string transactionDate);
    double totalPurchaseCostOnDate(std::string transactionDate);
    double totalPurchaseCost();
    List<purchase>& getPurchases() {return purchases;}
    std::string getMemberID(){ return memberID; }
    int size() const { return numberOfPurchases; }
    bool operator>(const memberPurchase& RHS){return memberID > RHS.memberID;}
\
    friend ostream& operator<<(ostream &out, List<purchase>& purch);

private:
    List<purchase> purchases;
    std::string memberID;
    int numberOfPurchases;
};

class purchaseHistory
{
    friend class memberPurchase;
public:
    // constructor
    purchaseHistory();
    // mutators
    void insertMemberPurchases(memberPurchase& newPurchases);
    // accessors
    bool isInList(memberPurchase& mem);
    node<memberPurchase>* search(memberPurchase& target);
    List<memberPurchase>& getTotalPurchases(){return totalPurchases;}
    int size() const { return numberOfTotalPurchases; }

private:
    List<memberPurchase> totalPurchases;
    int numberOfTotalPurchases;
};

#endif // PURCHASE_H
