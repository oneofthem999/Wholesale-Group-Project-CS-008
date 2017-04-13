#ifndef PURCHASE_H
#define PURCHASE_H

#include <iostream>
#include "thelist.h"
#include "Product.h"

using namespace std;

struct purchase
{
    string transactionDate;
    Product product;
    bool operator!=(const purchase& RHS);
    friend ostream& operator<<(ostream& out, purchase& purch);
};

class memberPurchase
{
public:
    // constructors
    memberPurchase();
    // mutators
    void addPurchase(std::string date, Product& item);
    //void changeID(std::string id);
    // accessors
    node<purchase>* search(Product& item);

    /*****************************************************
     * search the purchase record matches a specific date
     * if finds the match record, return the pointer and the position of the record
     * and search again with starting at the last position
     * if the it goes to the end, bool finish will be true to tell the upper level
     * that there is no more match record.
     ****************************************************/
    node<purchase>* search(string transactionDate, int& pos, bool& finish);
    node<purchase>* search(string transactionDate);
    double totalPurchaseCostOnDate(std::string transactionDate);
    double totalPurchaseCost();
    List<purchase>& getPurchases() {return purchases;}
    //std::string getMemberID(){ return memberID; }
    int size() const { return numberOfPurchases; }
    //bool operator>(const memberPurchase& RHS){return memberID > RHS.memberID;}
    void print();
    friend ostream& operator<<(ostream &out, List<purchase>& purch);

private:
    List<purchase> purchases;
    //std::string memberID;
    int numberOfPurchases;
};

#endif // PURCHASE_H
