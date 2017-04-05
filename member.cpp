#include "member.h"

member::member()
{
    memberPurchases = new memberPurchase();
    totalAmountSpent = 0;
    rebateAmount = 0;
    /*firstName = "John";
    lastName = "Doe";
    membershipNumber = "1234";
    membershipType = "Basic";
    expirationDate = "5/4/2017";*/
}

member::member(const member& other)
{
    if (this != &other)
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

void member::setName(std::string first, std::string last)
{
    firstName = first;
    lastName = last;
}

void member::setMembershipNumber(std::string number)
{
    membershipNumber = number;
}

bool member::setMembershipType(std::string type)
{
    if (type == "Basic" || type == "Preferred")
    {
        membershipType = type;
        return true;
    }
    return false;
}

void member::setExpirationDate(std::string date)
{
    expirationDate = date;
}

void member::enterPurchase(std::string date, Item item)
{
    setAmountSpent(memberPurchases->addPurchase(date, item));
    if (history.isInList(*memberPurchases))
        history.insertMemberPurchases(*memberPurchases);
}

void member::setAmountSpent(double amountToAdd)
{
    totalAmountSpent += amountToAdd;
}

void member::setRebateAmount()
{
    if (membershipType == "Preferred")
    {
        double rebate;
        rebateAmount = totalAmountSpent / 1.0875 * REBATE_RATE;
    }
}

bool member::shouldUpgradeOrDowngrade() const
{
    if (membershipType == "Basic")
    {
        double potentialRebate;
        potentialRebate = totalAmountSpent / 1.0875 * REBATE_RATE;
        if (potentialRebate > PREFERRED_DUES - BASIC_DUES)
            return true;
    }

    else
    {
        if (rebateAmount < PREFERRED_DUES - BASIC_DUES)
            return true;
    }

    return false;
}

bool member::operator<(const member& RHS) { return getFirstName() < RHS.getFirstName(); }
bool member::operator<=(const member& RHS) { return getFirstName() <= RHS.getFirstName(); }
bool member::operator>(const member& RHS) { return getFirstName() > RHS.getFirstName(); }
bool member::operator>=(const member& RHS) { return getFirstName() >= RHS.getFirstName(); }
bool member::operator==(const member& RHS) { return getFirstName() == RHS.getFirstName(); }
bool member::operator!=(const member& RHS) { return getFirstName() != RHS.getFirstName(); }

memberList::memberList()
{

}

void memberList::addMember(member mem)
{
    allMembers.InsertHead(mem);
    allMembers.sort();
}

void memberList::deleteMember(string firstName, string lastName)
{
    for (node<member>* temp = allMembers.begin(); temp != NULL; temp = temp->next)
    {
        if ((temp->item.getFirstName() == firstName) && (temp->item.getLastName() == lastName))
        {
            if (temp != allMembers.begin())
                allMembers.DeleteNode(temp);
            else
                allMembers.DeleteHead();
        }
    }
}

void memberList::deleteMember(string id)
{
    for (node<member>* temp = allMembers.begin(); temp != NULL; temp = temp->next)
    {
        if (temp->item.getID() == id)
        {
            if (temp != allMembers.begin())
                allMembers.DeleteNode(temp);
            else
                allMembers.DeleteHead();
        }
    }
}

memberPurchase* memberList::memberPurchaseSearch(string firstName, string lastName)
{
    for (node<member> *temp = allMembers.begin(); temp != NULL; temp = temp->next)
    {
        if ((temp->item.getFirstName() == firstName) && (temp->item.getLastName() == lastName))
            return temp->item.getMemberPurchase();
    }
    cout << "There is no member named " << firstName << " " << lastName << " stored in program." << endl;
    return NULL;
}

memberPurchase* memberList::memberPurchaseSearch(string id)
{
    for (node<member> *temp = allMembers.begin(); temp != NULL; temp = temp->next)
    {
        if (temp->item.getID() == id)
            return temp->item.getMemberPurchase();
    }
    cout << "There is no member with ID number " << id << " stored in program." << endl;
    return NULL;
}
