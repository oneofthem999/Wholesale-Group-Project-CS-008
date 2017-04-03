#include "purchase.h"

memberPurchase::memberPurchase()
{
    numberOfMemberPurchases = 0;
}

double memberPurchase::addPurchase(std::string date, Item item)
{
    purchase newTransaction;
    newTransaction.transactionDate = date;
    newTransaction.item = item;
    purchases.InsertHead(newTransaction);
    ++numberOfMemberPurchases;
    return newTransaction.item.getTotal();
}

purchaseHistory::purchaseHistory()
{
    numberOfTotalPurchases = 0;
}

bool purchaseHistory::insertMemberPurchases(memberPurchase newPurchases)
{
    totalPurchases.InsertHead(newPurchases);
    numberOfTotalPurchases += newPurchases.size();
}
