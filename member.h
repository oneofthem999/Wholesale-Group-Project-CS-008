#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include "purchase.h"

const double REBATE_RATE = 0.05;
const double BASIC_DUES = 60.00;
const double PREFERRED_DUES = 75.00;

class member
{
    friend class purchaseHistory;
    public:
        // CONSTRUCTORS AND DESTRUCTOR
        member();
        member(const member& other);
        ~member();
        // MODIFICATION MEMBER FUNCTIONS
        bool setName(std::string first, std::string last);
        bool setMembershipNumber(std::string number);
        bool setMembershipType(std::string type = "Basic");
        bool setExpirationDate(std::string date);
        bool enterPurchase(std::string date, std::string item,
                           double price, double quantity);
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
        bool addMember();
        bool deleteMember();
    private:
        List<member> allMembers;
};

#endif // MEMBER_H
