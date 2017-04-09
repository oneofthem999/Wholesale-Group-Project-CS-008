#include "member.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <QDebug>

using namespace std;

member::member()
{
    totalAmountSpent = 0;
    rebateAmount = 0;
    memberPurchases = new memberPurchase();
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
    memberPurchases = new memberPurchase();
    memberPurchases->changeID(membershipNumber);
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
        memberPurchases->changeID(number);
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

void member::enterPurchase(std::string date, Item& item)
{
    memberPurchases->addPurchase(date, item);
    setAmountSpent(item.getTotal());
}

void member::setAmountSpent(double amountToAdd)
{
    totalAmountSpent += amountToAdd;
    setRebateAmount();
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
    grandTotal = 0;
}

void memberList::addMember(member mem)
{
    if(search(mem.getID()) == NULL) // makes sure no member with duplicate ID is added
    {
        allMembers.InsertHead(mem);
        allMembers.sort();
        if(!mem.getMemberPurchase()->getPurchases().IsEmpty())
            allPurchases.insertMemberPurchases(*mem.getMemberPurchase());
        ++numberOfMembers;
    }
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
    node<member>* temp = search(id);
     if (temp != allMembers.begin())
        allMembers.DeleteNode(temp);
    else if (temp == allMembers.begin())
        allMembers.DeleteHead();
     else
         qDebug() << "There is no member with ID number " << QString::fromStdString(id) << " stored in program." << endl;
}

bool memberList::editMember(member &updated, std::string first, std::string last, std::string id, std::string type, std::string exp)
{
    node<member>* edit = search(updated.getID());
    if(!first.empty())
        edit->item.setName(first, edit->item.getLastName());
    if(!last.empty())
        edit->item.setName(edit->item.getFirstName(), last);
    if(!id.empty())
    {
        if(search(id) == NULL)
            edit->item.setMembershipNumber(id);
    }
    if(!type.empty())
        edit->item.setMembershipType(type);
    if(!exp.empty())
        edit->item.setExpirationDate(exp);
}

void memberList::addPurchases(node<member>* mem, std::string date, Item& item)
{
    mem->item.enterPurchase(date, item);
    allPurchases.insertMemberPurchases(*mem->item.getMemberPurchase());
    inventory.addToInventory(item);
    grandTotal += item.getTotal();
}

node<member>* memberList::search(std::string id)
{
    node<member>* temp = allMembers.begin();
    while(temp != NULL)
    {
        if (temp->item.getID() == id)
            return temp;
        temp = temp->next;
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
    qDebug() << "There is no member named " << QString::fromStdString(firstName) << " " << QString::fromStdString(lastName) << " stored in program." << endl;
    return NULL;
}

memberPurchase* memberList::memberPurchaseSearch(string id)
{
    node<member> *temp = search(id);
    if (temp != NULL)
        return temp->item.getMemberPurchase();
    qDebug() << "There is no member with ID number " << QString::fromStdString(id) << " stored in program." << endl;
    return NULL;
}

bool memberList::readMemberFile(std::string filename)
{

    fstream file;
    file.open(filename.c_str(), ios::in);
    string name;
    if(file.is_open()){
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
    file.open(filename.c_str(), ios_base::in);
    string date;
    if(file.is_open()){
        while(getline(file, date))
        {
            string itemname, memberID, numbers;
            stringstream ss;
            double price;
            int quantity;
            ss << date;
            ss >> date;
            getline(file,memberID);
            ss << memberID;
            ss >> memberID;
            getline(file, itemname);
            getline(file, numbers);
            ss << numbers;
            ss >> price >> quantity;
            Item purchased(itemname, price, quantity);
            node<member>* findMember = search(memberID);
            addPurchases(findMember, date, purchased);
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
