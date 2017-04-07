#include "purchase.h"
#include <QDebug>

bool purchase::operator!=(const purchase& RHS)
{ return ((transactionDate != RHS.transactionDate) || (item != RHS.item)); }

ostream& operator<<(ostream& out, purchase& purch)
{
    out << purch.transactionDate << endl
        << purch.item.getItemName() << endl
        << purch.item.getItemPrice() << "   "
        << purch.item.getItemQuantity() << endl;
    return out;
}

memberPurchase::memberPurchase()
{
    numberOfPurchases = 0;
}

void memberPurchase::addPurchase(std::string date, Item& item)
{
    purchase newTransaction;
    newTransaction.transactionDate = date;
    newTransaction.item = item;
    purchases.InsertHead(newTransaction);
    ++numberOfPurchases;
}

void memberPurchase::changeID(std::string id)
{
    memberID = id;
}

double memberPurchase::totalPurchaseCost()
{
    double total = 0;
    for (node<purchase> *temp = purchases.begin(); temp != NULL; temp = temp->next)
        total += temp->item.item.getTotal();
    return total;
}

double memberPurchase::totalPurchaseCostOnDate(string date)
{
    double total = 0;
    for (node<purchase> *temp = purchases.begin(); temp != NULL; temp = temp->next)
    {
        if (temp->item.transactionDate == date)
            total += temp->item.item.getTotal();
    }
    return total;
}

List<purchase>& memberPurchase::getPurchases() { return purchases; }

node<purchase>* memberPurchase::search(Item& itemComp)
{
    node<purchase> *temp = purchases.begin();
    {
        if (temp->item.item == itemComp)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

node<purchase>* memberPurchase::search(std::string transactionDateComp)
{
    node<purchase> *temp = purchases.begin();
    {
        if (temp->item.transactionDate == transactionDateComp)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

ostream& operator<<(ostream& out, memberPurchase& member)
{
    for (node<purchase>* temp = member.getPurchases().begin(); temp != NULL; temp = temp->next)
    {
        out << temp->item<< endl;
    }
    out << "Total of all purchases made by member: $" << member.totalPurchaseCost();
    return out;
}

purchaseHistory::purchaseHistory()
{
    numberOfTotalPurchases = 0;
}

bool purchaseHistory::isInList(memberPurchase &mem)
{
    bool result = true;
    for (node<memberPurchase>* temp = totalPurchases.begin(); temp != NULL; temp = temp->next)
    {
        for (node<purchase>* temp2 = temp->item.getPurchases().begin(), *temp3 = mem.getPurchases().begin();
             temp2 != NULL ; temp2 = temp2->next, temp3 = temp3->next)
        {
            if (temp2->item != temp3->item)
            {
                result = false;
                break;
            }
        }
    }
    return result;
}

node<memberPurchase>* purchaseHistory::search(memberPurchase& target)
{
    node<memberPurchase>* temp = totalPurchases.begin();
    while(temp != NULL)
    {
        if (temp->item.getMemberID() == target.getMemberID())
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void purchaseHistory::insertMemberPurchases(memberPurchase& newPurchases)
{
    node<memberPurchase>* found = search(newPurchases);
    if(found){
        numberOfTotalPurchases -= found->item.size();
        node<memberPurchase>* temp = found->next;
        *found = newPurchases;
        found->next = temp;
        numberOfTotalPurchases += found->item.size();
    }
    else{
        totalPurchases.InsertHead(newPurchases);
        totalPurchases.sort();
        numberOfTotalPurchases += newPurchases.size();
    }
}
