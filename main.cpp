#include <iostream>
#include <fstream>
#include <sstream>
#include "inventory.h"
#include "testfile.cpp"
#include "member.h"

using namespace std;

void theFormalProgram();

int main(int argc, char *argv[])
{
    //theListTEST();
    //memberTEST();
    //purchaseTEST();

    theFormalProgram();
    return 0;
}

void theFormalProgram(){
    inventory totalInventory;
    memberList totalMember;
    ifstream memberfile ("warehouse shoppers.txt");
    string name;

    //read member list
    if(memberfile.is_open()){
        while(getline(memberfile,name))
        {
            stringstream ss;
            string first, last, ID, type, exp;
            ss << name;
            ss >> first >> last;
            getline(memberfile,ID);
            ss << ID;
            ss >> ID;
            getline(memberfile,type);
            ss << type;
            ss >> type;
            getline(memberfile,exp);
            ss << exp;
            ss >> exp;
            member newMember;
            newMember.setName(first, last);
            newMember.setMembershipNumber(ID);
            newMember.setMembershipType(type);
            newMember.setExpirationDate(exp);
            totalMember.addMember(newMember);
        }
        memberfile.close();
    }

    //read purchase history
    string date;
    string memberID;
    string productName;
    string numbers;
    double productPrice;
    int productQuantity;
    stringstream ss;
    ifstream file ("day1.txt");
    if (file.is_open())
    {
        while ( getline (file,date) )
        {
            //get information from file
            ss << date;
            ss >> date;
            getline(file,memberID);
            ss << memberID;
            ss >> memberID;
            getline(file, productName);
            getline(file, numbers);
            stringstream ssnum;
            ssnum << numbers;
            ssnum >> productPrice >> productQuantity;
            Product thisOne(productName,productPrice,productQuantity);
            totalInventory.addToInventory(thisOne);
            totalMember.addPurchases(totalMember.search(memberID),date,thisOne);
        }
        file.close();
    }

    //2. enter ID or name, get member purchase history
    cout<<"search ID 88888: "<<endl;
    node<member>* target;
    target=totalMember.search("88888");
    if(target){
        target->item.printPurchaseHistory();
    }
    else
        cout<<"not found!"<<endl;
    cout<<endl;

    cout<<"search name Fred Frugal: "<<endl;
    target=totalMember.search("Frugal","Fred");
    if(target)
        target->item.printPurchaseHistory();
    else
        cout<<"not found!";

    //3. prints the total purchases by all the members sorted by membership number.
    //   with a grand total of the purchases.
    totalMember.print();

    cout<<"grandtotal = $"<<totalMember.getGrandTotal()<<endl;

    //4. enter an item name, get quantity and total sales price
    cout<<endl;
    cout<<"search ground beef for its quantity and total sales price"<<endl;
    node<Product>* targetProduct;
    targetProduct = totalInventory.search("Ground Beef");
    if(targetProduct){
        cout<<"name: "<<targetProduct->item.getName()<<" | "<<targetProduct->item.getQuantity()<<endl;
        cout<<"subtotal (before tax): $"<<targetProduct->item.getSubtotal()<<endl;
        cout<<"total sales price(with tax): $"<<targetProduct->item.getTotal()<<endl;
    }
    else
        cout<<"not found!"<<endl;
}
