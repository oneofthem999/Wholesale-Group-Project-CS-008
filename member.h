#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include "purchase.h"
#include "inventory.h"

using namespace std;

const double REBATE_RATE = 0.05;
const double BASIC_DUES = 60.00;
const double PREFERRED_DUES = 75.00;

class member
{
    public:
        // CONSTRUCTORS AND DESTRUCTOR
        member();
        member(string first, string last, string id,
               string type, string date);
        // MODIFICATION MEMBER FUNCTIONS
        bool setName(string first, string last);
        bool setMembershipNumber(string number);
        bool setMembershipType(string type = "Basic");
        bool setExpirationDate(string date);
        void enterPurchase(string date, Product &item);
        void setAmountSpent(double amountToAdd);

        void setRebateAmount();

        // CONSTANT MEMBER FUNCTIONS
        std::string getFirstName() const      {return firstName;}
        std::string getLastName() const       {return lastName;}
        std::string getFullName() const       {return firstName + " " + lastName;}
        std::string getID() const             {return membershipNumber;}
        std::string getMembershipType() const {return membershipType;}
        std::string getExpirationDate() const {return expirationDate;}
        double getAmountSpent() const         {return totalAmountSpent;}
        double getRebateAmount() const        {return rebateAmount;}

        node<purchase>* searchPurchase(string transactionDate, int& pos, bool& finish);

        bool shouldUpgradeOrDowngrade() const;
        void printPurchaseHistory();
        bool operator>(const member& RHS);
        bool operator<(const member& RHS);
        bool operator>=(const member& RHS);
        bool operator<=(const member& RHS);
        bool operator==(const member& RHS);
        bool operator!=(const member& RHS);

        friend ostream& operator<<(ostream& out, member& x);

    private:
        std::string firstName;
        std::string lastName;
        std::string membershipNumber;
        std::string membershipType;
        std::string expirationDate;
        double totalAmountSpent;
        double rebateAmount;
        memberPurchase personalPurchases;
};

class memberList    //default sort by ID with increasing order
{
    friend class member;
    public:
        // constructor
        memberList();
        // mutators
        void addMember(member mem);
        void deleteMember(string firstName, string LastName);
        void deleteMember(string id);
        bool editMember(member &updated, std::string first="", std::string last="", std::string id="", std::string type="", std::string exp="");
        void addPurchases(node<member>* mem, std::string date, Product &item);

        // accessors
        node<member>* search(string id);
        node<member>* search(string lastName,string firstName);

        /********************************************************************
         * node<purchase>* searchPurchaseByDate(string date, int& memPos, int& purPos, bool& finish);
         * search the purchase record matches a specific date
         * if finds the match record, return the pointer and the position of the record
         * and search again with starting at the last position
         * if the it goes to the end, bool finish will be true to tell the upper level
         * that there is no more match record.
         ******************************************************************/
        node<purchase>* searchPurchaseByDate(string date, int& memPos, int& purPos, bool& finish);

        /*******************************************************************
         * string getID(int pos);
         * return the ID of the (pos)th member
         * if pos is not valid, return "-1"
         * *pos start with 0( the first index is 0)
         *****************************************************************/
        string getID(int pos);

        List<member>& getMembers() {return allMembers;}
        double getGrandTotal() const {return grandTotal;}
        int size() const {return numberOfMembers;}
        void print();
        void printAllPurchase();
        friend ostream& operator<<(ostream& out, memberList& x);

    private:
        List<member> allMembers;
        double grandTotal;
        int numberOfMembers;
};


#endif // MEMBER_H
