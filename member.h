#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include <iostream>
#include "purchase.h"
#include "inventory.h"

const double REBATE_RATE = 0.05;
const double BASIC_DUES = 60.00;
const double PREFERRED_DUES = 75.00;

class member
{
    friend class purchaseHistory;
    public:
        // CONSTRUCTORS AND DESTRUCTOR
        member();
        member(std::string first, std::string last, std::string id,
               std::string type, std::string date);
        member(const member& other);
        member& operator=(const member& other);
        ~member();
        // MODIFICATION MEMBER FUNCTIONS
        bool setName(std::string first, std::string last);
        bool setMembershipNumber(std::string number);
        bool setMembershipType(std::string type = "Basic");
        bool setExpirationDate(std::string date);
        void enterPurchase(std::string date, Item &item);
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
        memberPurchase* getMemberPurchase()   { return memberPurchases; }
        bool shouldUpgradeOrDowngrade() const;

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
        memberPurchase* memberPurchases;
};

class memberList
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
        void addPurchases(node<member>* mem, std::string date, Item &item);
        bool readMemberFile(std::string filename);
        bool readSalesFile(std::string filename);
        // accessors
        node<member>* search(string id);
        node<member>* search(string firstName, string lastName);
        memberPurchase* memberPurchaseSearch(string firstName, string LastName);
        memberPurchase* memberPurchaseSearch(string id);
        List<member>& getMembers() {return allMembers;}
        purchaseHistory& getAllPurchases() {return allPurchases;}
        Inventory& getInventory() {return inventory;}
        double getGrandTotal() const {return grandTotal;}
        int size() const {return numberOfMembers;}
        friend ostream& operator<<(ostream& out, memberList& x);

    private:
        List<member> allMembers;
        purchaseHistory allPurchases;
        Inventory inventory;
        double grandTotal;
        int numberOfMembers;
};

#endif // MEMBER_H
