#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include <iostream>
#include "purchase.h"

const double REBATE_RATE = 0.05;
const double BASIC_DUES = 60.00;
const double PREFERRED_DUES = 75.00;

class member
{
    friend class purchaseHistory;
    public:
//        static purchaseHistory history;
        // CONSTRUCTORS AND DESTRUCTOR
        member();
        member(std::string first, std::string last, std::string number,
               std::string type, std::string date);
        member(const member& other);
        member& operator=(const member& other);
        ~member();
        // MODIFICATION MEMBER FUNCTIONS
        bool setName(std::string first, std::string last);
        bool setMembershipNumber(std::string number);
        bool setMembershipType(std::string type = "Basic");
        bool setExpirationDate(std::string date);
        bool insertPurchase(std::string date, Item item);
        bool setAmountSpent(double amountToAdd);
        bool setRebateAmount();
        // CONSTANT MEMBER FUNCTIONS
        std::string getFirstName() const      {return firstName;}
        std::string getLastName() const       {return lastName;}
        std::string getID() const             {return membershipNumber;}
        std::string getMembershipType() const {return membershipType;}
        std::string getExpirationDate() const {return expirationDate;}
        double getAmountSpent() const         {return totalAmountSpent;}
        double getRebateAmount() const        {return rebateAmount;}
        memberPurchase* getPurchases() const  {return memberPurchases;}
        bool shouldUpgradeOrDowngrade() const;

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
        memberList();
        ~memberList();
        void addMember(member &newMember);
        void deleteMember(const member &memberToDelete);
        member findMember(std::string ID);
        bool readMemberFile(std::string filename);
        bool readSalesFile(std::string filename);
        purchaseHistory getAllPurchases() const {return allPurchases;}
        friend ostream& operator<<(ostream& out, memberList& x);

    private:
        List<member> allMembers;
        purchaseHistory allPurchases;
};

#endif // MEMBER_H
