#include "member.h"
#include <fstream>
#include <cctype>

member::member()
{
    totalAmountSpent = 0;
    rebateAmount = 0;
    memberPurchases = new memberPurchase;
//    history.insertMemberPurchases(*memberPurchases);
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
        if(!isalpha(ch) && ch != ' ' && ch != '-')
            return false;
    }
    for(size_t i = 0; i < last.length() - 1; ++i)
    {
        char ch = last[i];
        if(!isalpha(ch) && ch != ' ' && ch != '-')
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

bool member::insertPurchase(std::string date, Item item)
{
    // add error checking
    double total = memberPurchases->addPurchase(date, item);
    setAmountSpent(total);
    return true;
}

bool member::setAmountSpent(double amountToAdd)
{
    // add error checking
    totalAmountSpent += amountToAdd;
    return true;
}

bool member::setRebateAmount()
{
    if(membershipType == "Preferred")
    {
        double totalWithNoTax = totalAmountSpent / 1.0875;
        rebateAmount = totalWithNoTax * REBATE_RATE;
        return true;
    }
    return false;
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


memberList::memberList()
{

}

memberList::~memberList()
{

}

void memberList::addMember(member &newMember)
{
    allMembers.InsertHead(newMember);
    allPurchases.insertMemberPurchases(*newMember.getPurchases());
}

void memberList::deleteMember(const member &memberToDelete)
{
//    List<member>::Iterator iter = allMembers.Search(memberToDelete);
//    allMembers.DeleteNode(iter);
}

member memberList::findMember(std::string ID)
{
    List<member>::Iterator it = allMembers.begin();
    while(it != allMembers.end())
    {
        member cursor = *it;
        if(cursor.getID() == ID)
            return cursor;
    }
}

bool memberList::readMemberFile(std::string filename)
{
    fstream file;
    file.open(filename, ios::in);
    if(!file)
        return false;
    string line;
    while(!file.eof())
    {
        member newMember;
        string first, last, ID, type, exp;
        file >> first >> last >> ID >> type >> exp;
        newMember.setName(first, last);
        newMember.setMembershipNumber(ID);
        newMember.setMembershipType(type);
        newMember.setExpirationDate(exp);
        addMember(newMember);
    }
    return true;
}

bool memberList::readSalesFile(std::string filename)
{
    fstream file;
    file.open(filename, ios::in);
    if(!file)
        return false;
    string line;
    while(!file.eof())
    {
        purchase newPurchase;
        string date, memberID, itemname;
        double price;
        int quantity;
        file >> date >> memberID >> itemname >> price >> quantity;
        member purchaser = findMember(memberID);
        Item itembought(itemname, price, quantity);
        purchaser.insertPurchase(date, itembought);
    }
    return true;
}

ostream& operator<<(ostream& out, memberList& x)
{
    List<member>::Iterator it = x.allMembers.begin();
    while(it != x.allMembers.end())
    {
        member* cursor = &*it;
        out << cursor->getFirstName() << " " <<cursor->getLastName() << " "
            << cursor->getID() << " " << cursor->getMembershipType() << " "
            << cursor->getExpirationDate() << " "
            << cursor->getPurchases()->size() << "\n";
        it.next();
    }

    return out;
}
