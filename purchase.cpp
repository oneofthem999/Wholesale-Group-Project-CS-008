#include "purchase.h"

memberPurchase::memberPurchase()
{
    numberOfMemberPurchases = 0;
}

double memberPurchase::addPurchase(std::string date, std::string item,
                 double price, double quantity)
{
    purchase newTransaction;
    newTransaction.transactionDate = date;
    newTransaction.itemName = item;
    newTransaction.itemPrice = price;
    newTransaction.itemQuantity = quantity;
    newTransaction.subtotal = price * quantity;
    newTransaction.tax = newTransaction.subtotal * SALES_TAX_RATE;
    newTransaction.total = newTransaction.subtotal + newTransaction.tax;
    purchases.InsertHead(newTransaction);
    ++numberOfMemberPurchases;
    return newTransaction.total;
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
