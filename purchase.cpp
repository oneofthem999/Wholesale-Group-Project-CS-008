#include "purchase.h"

ostream& operator<<(ostream& out, purchase& purch)
{
    out << purch.transactionDate << endl
        << purch.product.getName() << endl
        << purch.product.getPrice() << "   "
        << purch.product.getQuantity() << endl;
    return out;
}

memberPurchase::memberPurchase()
{
    numberOfPurchases = 0;
}

void memberPurchase::addPurchase(std::string date, Product& item)
{
    purchase newTransaction;
    newTransaction.transactionDate = date;
    newTransaction.product = item;
    purchases.Insert(newTransaction);
    ++numberOfPurchases;
}



double memberPurchase::totalPurchaseCost()
{
    double total = 0;
    for (node<purchase> *temp = purchases.begin(); temp != NULL; temp = temp->next)
        total += temp->item.product.getTotal();
    return total;
}

double memberPurchase::totalPurchaseCostOnDate(string date)
{
    double total = 0;
    for (node<purchase> *temp = purchases.begin(); temp != NULL; temp = temp->next)
    {
        if (temp->item.transactionDate == date)
            total += temp->item.product.getTotal();
    }
    return total;
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

node<purchase>* memberPurchase::search(string transactionDate, int& pos, bool& finish){
    node<purchase> *purchaseWalker = purchases.begin();
    for(int i=0; i<pos; i++){
        if(purchaseWalker->next){
            purchaseWalker=purchaseWalker->next;
        }
        else{
            finish=true;
            return NULL;
        }
    }//point to (pos)th

    while(purchaseWalker){//is not null
        pos++;
        if(purchaseWalker->item.transactionDate==transactionDate)
            return purchaseWalker;
        else{
            purchaseWalker=purchaseWalker->next;
        }
    }
    finish=true;
    return NULL;
}

void memberPurchase::print(){
    for (node<purchase>* temp = purchases.begin(); temp != NULL; temp = temp->next)
    {
        cout << temp->item<< endl;
    }
    cout << "Total of all purchases made by member: $" << totalPurchaseCost()<<endl;

}

