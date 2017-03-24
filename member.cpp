#include "member.h"

member::member()
{
//    insertMemberPurchases(memberPurchases);
    totalAmountSpent = 0;
    rebateAmount = 0;
}

member::member(const member& other)
{
    if(this != &other)
    {
        firstName = other.firstName;
        lastName = other.lastName;
        membershipNumber = other.membershipNumber;
        membershipType = other.membershipType;
        expirationDate = other.expirationDate;
        memberPurchases = other.memberPurchases;
        totalAmountSpent = other.totalAmountSpent;
        rebateAmount = other.rebateAmount;
    }
}

member::~member()
{
    memberPurchases = NULL;
}

bool member::setName(std::string first, std::string last)
{
    firstName = first;
    lastName = last;
}

bool member::setMembershipNumber(std::string number)
{
    membershipNumber = number;
}

bool member::setMembershipType(std::string type)
{
    if(type == "Basic" || type == "Preferred")
    {
        membershipType = type;
        return true;
    }
    return false;
}

bool member::setExpirationDate(std::string date)
{
    expirationDate = date;
}

bool member::enterPurchase(std::string date, std::string item,
                   double price, double quantity)
{
    setAmountSpent(memberPurchases->addPurchase(date, item, price, quantity));
}

bool member::setAmountSpent(double amountToAdd)
{
    totalAmountSpent += amountToAdd;
}

bool member::setRebateAmount()
{
    if(membershipType == "Preferred")
    {
        double rebate;
        rebateAmount = totalAmountSpent / 1.0875 * REBATE_RATE;
    }
}

bool member::shouldUpgradeOrDowngrade() const
{
    if(membershipType == "Basic")
    {
        double potentialRebate;
        potentialRebate = totalAmountSpent / 1.0875 * REBATE_RATE;
        if(potentialRebate > PREFERRED_DUES - BASIC_DUES)
            return true;
    }

    else
    {
        if(rebateAmount < PREFERRED_DUES - BASIC_DUES)
            return true;
    }

    return false;
}
