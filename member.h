#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include "purchase.h"

const double REBATE_RATE = 0.05;
const double BASIC_DUES = 60.00;
const double PREFERRED_DUES = 75.00;

static purchaseHistory history = purchaseHistory();

class member
{
    friend class purchaseHistory;
public:
    // CONSTRUCTORS AND DESTRUCTOR
    member();
    member(const member& other);
    ~member();
    // MODIFICATION MEMBER FUNCTIONS
    void setName(std::string first, std::string last);
    void setMembershipNumber(std::string number);
    bool setMembershipType(std::string type = "Basic");
    void setExpirationDate(std::string date);
    void enterPurchase(std::string date, Item item);
    void setAmountSpent(double amountToAdd);
    void setRebateAmount();
    // CONSTANT MEMBER FUNCTIONS
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getID() const { return membershipNumber; }
    std::string getMembershipType() const { return membershipType; }
    std::string getExpirationDate() const { return expirationDate; }
    double getAmountSpent() const { return totalAmountSpent; }
    double getRebateAmount() const { return rebateAmount; }
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
    void addMember(member mem);
    void deleteMember(string firstName, string LastName);
    void deleteMember(string id);
private:
    List<member> allMembers;
};

#endif // MEMBER_H
