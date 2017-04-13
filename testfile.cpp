#include "inventory.h"
#include "purchase.h"
#include "member.h"

void memberTEST(){
    //member test
    cout<<"*** memberTEST ***"<<endl;
    member peter("Peter","A","123","Basic","03/05/1913");
    Product milk("1 gallon milk", 2.49, 13);
    peter.enterPurchase("03/05/2013",milk);
    cout<<peter<<endl;
    peter.printPurchaseHistory();
    cout<<endl;
    member peter2=peter;
    cout<<peter2<<endl;
    peter2.printPurchaseHistory();
    //search
    cout<<"search on 03/05/2013"<<endl;
    int pos=0;
    bool f=false;
    node<purchase>* result;
    while(!f){
        result = peter.searchPurchase("03/05/2013",pos,f);
        if(result)
            cout<<result->item;
    }
    cout<<" *** memberTEST completed *** "<<endl;

    Product car("car", 30000, 1);
    Product apple("apple", 2, 20);

    peter.enterPurchase("03/05/2013",car);
    peter.enterPurchase("03/06/2013",apple);

    cout<<" *** memberList TEST *** "<<endl;
    memberList aList;
    member Mary("Mary", "B", "456","Preferred", "03/06/1913");
    Mary.enterPurchase("03/05/2013",apple);
    aList.addMember(peter);
    aList.addMember(Mary);
    aList.printAllPurchase();

    //search
    cout<<"search purchases on 03/05/2013"<<endl;
    int memP=0;
    int PurP=0;
    bool finish=false;
    while(!finish){
        node<purchase>* result;
        result = aList.searchPurchaseByDate("03/05/2013",memP,PurP,finish);
        if(result)
            cout<<result->item;
    }
    cout<<" *** memberList TEST completed *** "<<endl;
}

void purchaseTEST(){
    memberPurchase a;
    Product milk("1 gallon milk", 2.49, 13);
    a.addPurchase("03/05/2013", milk);
    a.print();
    Product apple("apple", 4.9, 25);
    a.addPurchase("03/06/2013", apple);
    a.print();
    Product car("car",30000,1);
    a.addPurchase("03/05/2013",car);

    //search on date 03/05/2013
    cout<<"all the purchase on 03/05/2013"<<endl;
    int pos=0;
    bool finish = false;
    node<purchase>* result;
    while(!finish){
        result=a.search("03/05/2013",pos,finish);
        if(result)
            cout<<result->item;
    }
}

void productNinventoryTEST(){
    //product
    cout<<"*** product test ***"<<endl;
    Product milk("1 gallon milk", 2.49, 13);
    cout<<"the product name:      "<<milk.getName()<<endl
        <<"            price:     $"<<milk.getPrice()<<endl
        <<"            quantity: *"<<milk.getQuantity()<<endl
        <<"            subtotal:  "<<milk.getSubtotal()<<endl
        <<"            tax:       $"<<milk.getTax()<<endl
        <<"            total:     $"<<milk.getTotal()<<endl;

    //Inventory
    cout<<"*** inventory test ***"<<endl;
    //add
    inventory testInventory;
    cout<<"add milk: "<<endl;
    testInventory.addToInventory(milk);
    cout<<"inventory: "<<endl;
    testInventory.print();

    cout<<"add 3 apple price: 5"<<endl;
    testInventory.addToInventory("apple", 5,3);
    cout<<"inventory: "<<endl;
    testInventory.print();

    cout<<"add 5 apple price: 5"<<endl;
    testInventory.addToInventory("apple", 5,5);
    cout<<"inventory: "<<endl;
    testInventory.print();

    //sort
    cout<<"add 3 z price: 5"<<endl;
    testInventory.addToInventory("z", 5,3);
    cout<<"inventory: "<<endl;
    testInventory.print();

    cout<<"add 3 f price: 5"<<endl;
    testInventory.addToInventory("f", 5,3);
    cout<<"inventory: "<<endl;
    testInventory.print();

    //search and delete
    testInventory.deleteFromInventory(milk);
    cout<<"inventory: "<<endl;
    testInventory.print();
    testInventory.deleteFromInventory("apple");
    cout<<"inventory: "<<endl;
    testInventory.print();

    cout<<"**** Product and Inventory test completed. ****"<<endl<<endl<<endl;
}

void theListTEST(){
    List<int> testLinkList;
    //isEmpty
    if(testLinkList.IsEmpty())
        cout<<"The link list is empty now."<<endl;

    //insert
    cout<<"insert 1, insert 2, insert 3. the link list is now :"<<endl;
    testLinkList.Insert(1);
    testLinkList.Insert(2);
    testLinkList.Insert(3);
    node<int>* walker=testLinkList.begin();
    while(walker){
        cout<<walker->item<<" ";
        walker=walker->next;
    }
    cout<<endl<<endl;

    //insertHead
    cout<<"insertHead (4)"<<endl;
    testLinkList.InsertHead(4);
    cout<<"the list is now: ";
    walker=testLinkList.begin();
    while(walker){
        cout<<walker->item<<" ";
        walker=walker->next;
    }
    cout<<endl<<endl;

    //insertAfter and insertBefore and Search
    cout<<"insertAfter 2 with value 5"<<endl;
    testLinkList.InsertAfter(5,testLinkList.Search(2));
    cout<<"insertBefore 2 with value 6"<<endl;
    testLinkList.InsertBefore(6,testLinkList.Search(2));
    cout<<"the list is now: ";
    walker=testLinkList.begin();
    while(walker){
        cout<<walker->item<<" ";
        walker=walker->next;
    }
    cout<<endl<<endl;

    //sort
    cout<<"sort:"<<endl;
    testLinkList.sort();
    cout<<"the list is now: ";
    walker=testLinkList.begin();
    while(walker){
        cout<<walker->item<<" ";
        walker=walker->next;
    }
    cout<<endl<<endl;

    //copy of big 3
    List<int> test2 = testLinkList;
    walker=test2.begin();
    while(walker){
        cout<<walker->item<<" ";
        walker=walker->next;
    }
    cout<<endl<<endl;

    //isEmpty
    if(!testLinkList.IsEmpty())
        cout<<"the list is not empty now."<<endl<<endl;

    //deleteHead, deleteNode, deleteAll
    cout<<"deleteHead"<<endl;
    testLinkList.DeleteHead();
    walker=testLinkList.begin();
    while(walker){
        cout<<walker->item<<" ";
        walker=walker->next;
    }
    cout<<endl<<endl;

    cout<<"deleteNode (3)"<<endl;
    testLinkList.DeleteNode(testLinkList.Search(3));
    walker=testLinkList.begin();
    while(walker){
        cout<<walker->item<<" ";
        walker=walker->next;
    }
    cout<<endl;
    cout<<"deleteNode (2)"<<endl;
    testLinkList.DeleteNode(testLinkList.begin());
    walker=testLinkList.begin();
    while(walker){
        cout<<walker->item<<" ";
        walker=walker->next;
    }
    cout<<endl<<endl;

    //deleteAll
    if(!testLinkList.IsEmpty())
        cout<<"the list is not empty now."<<endl;
    cout<<"deleteAll"<<endl;
    testLinkList.DeleteAll();
    if(testLinkList.IsEmpty())
        cout<<"the list is empty now."<<endl<<endl;
    cout<<"*** the test for thelist.h completed. ***"<<endl<<endl<<endl<<endl;
}
