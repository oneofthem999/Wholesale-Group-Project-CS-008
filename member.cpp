#include "member.h"
#include <fstream>
#include <cctype>
#include <sstream>
#include <QDebug>

member::member()
{
    totalAmountSpent = 0;
    rebateAmount = 0;
    memberPurchases = new memberPurchase;
}

member::member(std::string first, std::string last, std::string number,
               std::string type, std::string date)
{
    firstName = first;
    lastName = last;
    membershipNumber = number;
    expirationDate = date;
    membershipType = type;
    totalAmountSpent = 0;
    rebateAmount = 0;
    memberPurchases = new memberPurchase;
}

member::member(const member& other)
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

member& member::operator=(const member& other)
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
    return *this;
}

member::~member()
{
    memberPurchases = NULL;
}

bool member::setName(std::string first, std::string last)
{
    for(size_t i = 0; i < first.length() - 1; ++i)
    {
        char ch = first[i];
        if(!isalpha(ch) && ch != '-')
            return false;
    }
    for(size_t i = 0; i < last.length() - 1; ++i)
    {
        char ch = last[i];
        if(!isalpha(ch) && ch != '-')
            return false;
    }
    first[0] = toupper(first[0]);
    last[0] = toupper(last[0]);
    firstName = first;
    lastName = last;
    return true;
}

bool member::setMembershipNumber(std::string number)
{
    if(number.find_first_not_of("0123456789") == std::string::npos)
    {
        membershipNumber = number;
        return true;
    }
    return false;
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
    // add error checking
    expirationDate = date;
    return true;
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
    if(membershipType == "Preferred")
    {
        double totalWithNoTax = totalAmountSpent / 1.0875;
        rebateAmount = totalWithNoTax * REBATE_RATE;
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

bool member::operator<(const member& RHS) { return getFirstName() < RHS.getFirstName(); }
bool member::operator<=(const member& RHS) { return getFirstName() <= RHS.getFirstName(); }
bool member::operator>(const member& RHS) { return getFirstName() > RHS.getFirstName(); }
bool member::operator>=(const member& RHS) { return getFirstName() >= RHS.getFirstName(); }
bool member::operator==(const member& RHS) { return getFirstName() == RHS.getFirstName(); }
bool member::operator!=(const member& RHS) { return getFirstName() != RHS.getFirstName(); }

ostream& operator<<(ostream& out, member& x)
{
    out << x.getFirstName() << " " << x.getLastName()  << "\n"
        << x.getID() << "\n"
        << x.getMembershipType() << "\n"
        << x.getExpirationDate() << "\n";
    return out;
}



memberList::memberList()
{
    numberOfMembers = 0;
}

void memberList::addMember(member mem)
{
    allMembers.InsertHead(mem);
    allMembers.sort();
    ++numberOfMembers;
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

node<member>* memberList::search(std::string id)
{
    for (node<member>* temp = allMembers.begin(); temp != NULL; temp = temp->next)
    {
        if (temp->item.getID() == id)
            return temp;
    }
    return NULL;
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

void memberList::updateMemberName(member &updated, std::string first, std::string last)
{
    search(updated.getID())->item.setName(first, last);
}

bool memberList::readMemberFile(std::string filename)
{
    fstream file;
    file.open(filename, ios::in);
    if(file.is_open()){
        string name;
        while(getline(file,name))
        {
            stringstream ss;
            string first, last, ID, type, exp;
            ss << name;
            ss >> first >> last;
            getline(file,ID);
            ss << ID;
            ss >> ID;
            getline(file,type);
            ss << type;
            ss >> type;
            getline(file,exp);
            ss << exp;
            ss >> exp;

            member newMember;
            newMember.setName(first, last);
            newMember.setMembershipNumber(ID);
            newMember.setMembershipType(type);
            newMember.setExpirationDate(exp);
            addMember(newMember);
        }
        file.close();
        return true;
    }
    return false;
}

bool memberList::readSalesFile(std::string filename)
{
    fstream file;
    file.open(filename, ios::in);
    string date;
    if(file.is_open()){
        while(getline(file, date))
        {
            string itemname, memberID, numbers;
            stringstream ss;
            double price;
            int quantity;
            getline(file,memberID);
            getline(file, itemname);
            getline(file, numbers);
            ss << numbers;
            ss >> price >> quantity;
            Item item(itemname, price, quantity);
            node<member>* findMember = search(memberID);
            findMember->item.enterPurchase(date, item);
        }
        return true;
    }
    return false;
}

ostream& operator<<(ostream& out, memberList& x)
{
    node<member>* cursor = x.allMembers.begin();
    while(cursor != NULL)
    {
        out << cursor->item;
        cursor = cursor->next;
    }
    return out;
}
