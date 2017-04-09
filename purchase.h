#ifndef PURCHASE_H
#define PURCHASE_H
#include <string>
#include "thelist.h"
#include "item.h"

struct purchase
{
    std::string transactionDate;
    Item item;
    bool operator!=(const purchase& RHS);
    friend ostream& operator<<(ostream& out, purchase& purch);
};

class memberPurchase
{
public:
    // constructors
    memberPurchase();
    memberPurchase(std::string id);
    // mutators
    void addPurchase(std::string date, Item& item);
    void changeID(std::string id);
    // accessors
    node<purchase>* search(Item& item);

    /*****************************************************
     * search the purchase record matches a specific date
     * if finds the match record, return the pointer and the position of the record
     * and search again with starting at the last position
     * if the it goes to the end, bool finish will be true to tell the upper level
     * that there is no more match record.
     ****************************************************/
    node<purchase>* search(string transactionDate, int& pos, bool& finish);
    node<purchase>* search(std::string transactionDate);//search by date
    double totalPurchaseCostOnDate(std::string transactionDate);
    double totalPurchaseCost();
    List<purchase>& getPurchases() {return purchases;}
    std::string getMemberID(){ return memberID; }
    int size() const { return numberOfPurchases; }
    bool operator>(const memberPurchase& RHS){return memberID > RHS.memberID;}

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

    /********************************************************************
     * node<purchase>* searchByDate(string date, int& member, int& purchase, bool& finish);
     * search the purchase record matches a specific date
     * if finds the match record, return the pointer and the position of the record
     * and search again with starting at the last position
     * if the it goes to the end, bool finish will be true to tell the upper level
     * that there is no more match record.
     ******************************************************************/
    node<purchase>* searchByDate(string date, int& memberPos, int& purchasePos, bool& finish);    //added

    /*******************************************************************
     * string getID(int pos);
     * return the ID of the (pos)th member
     * if pos is not valid, return "-1"
     * *pos start with 0( the first index is 0)
     *****************************************************************/
    string getID(int pos);
    List<memberPurchase>& getTotalPurchases(){return totalPurchases;}
    int size() const { return numberOfTotalPurchases; }

private:
    List<memberPurchase> totalPurchases;
    int numberOfTotalPurchases;
};

#endif // PURCHASE_H
