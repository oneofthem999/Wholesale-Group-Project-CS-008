#ifndef THENODE
#define THENODE
#include <iostream>

using namespace std;

//typedef int ItemType;
template <class ItemType>
struct node
{
    ItemType item;
    node* next;

    node();
    node(const ItemType& value);

    template <class ItemTypeF>
    friend ostream& operator << (ostream& outs, const node<ItemTypeF> *&printMe);
};

template <class ItemType>
node<ItemType>::node() {
    next = NULL;
}

template <class ItemType>
node<ItemType>::node(const ItemType& value) {
    next = NULL;
    item = value;
}


/*************************************************
* previous:
*  return the address of the previous node
* pre:
* post:
*  return NULL if looking for the previous of the first node
*************************************************/
template <class ItemType>
node<ItemType>* previous(node<ItemType>* head, node<ItemType>* beforeMe);

/*************************************************
* search:
*  return the address of the node with the specific item value
* pre:
* post:
*  return NULL if there is no such value
*************************************************/
template <class ItemType>
node<ItemType>* search(const ItemType &key, node<ItemType>* head);

/*************************************************
* insertHead:
*  insert a node at the head of linked list
* pre:
* post:
*************************************************/
template <class ItemType>
void insertHead(const ItemType &insertMe, node<ItemType>* &head);

/*************************************************
* insertAfter:
*  insert a node after the specific node
* pre:
* post:
*  return the address of the new node
*************************************************/
template <class ItemType>
node<ItemType>* insertAfter(const ItemType &insertMe, node<ItemType>* afterMe);

/*************************************************
* insertBefore:
*  insert a node before a specific node
* pre:
* post:
*  return the address of the new node
*************************************************/
template <class ItemType>
node<ItemType>* insertBefore(node<ItemType>* &head, const ItemType &insertMe, node<ItemType>* beforeMe);

template <class ItemType>
node<ItemType>* insert(node<ItemType>* &head, const ItemType &insertMe);

/*************************************************
* deleteNode:
*  delete a node in a linked list
* pre:
* post:
*  return the item value of the node that deleted
*************************************************/
template <class ItemType>
ItemType deleteNode(node<ItemType>* head, node<ItemType>* deleteMe);

template <class ItemType>
ItemType deleteHead(node<ItemType>* &head);

/*************************************************
* removeNode:
*  CANNOT remove the first one, use RemoveHead to do so
*  remove a node in a specific node from a linked list. The node won't be deleted.
* pre:
* post:
*  return the address of the removed node
*************************************************/
template <class ItemType>
node<ItemType>* removeNode(node<ItemType>* head, node<ItemType>* removeMe);

template <class ItemType>
node<ItemType>* removeHead(node<ItemType>* &head);

/*************************************************
* deleteAll:
*  delete all the nodes of a linked list
* pre:
* post:
*************************************************/
template <class ItemType>
void deleteAll(node<ItemType>* &head);

/*************************************************
* copy:
*  copy the whole linked list
* pre:
* post:
*  return the new head pointer of the new linked list
*************************************************/
template <class ItemType>
node<ItemType>* copy(node<ItemType>* sourceHead);

/*************************************************
* print:
*  put the linked list in a out stream
* pre:
* post:
*  used to output a linked list.
*************************************************/
template <class ItemType>
void print(node<ItemType>* head, ostream &out);

/*************************************************
* WhereThisGoes:
*  Takes a value (item) and returns a pointer to the node after which the item belongs in the list.
* pre:
*  take a itemtype
* post:
*  Returns NULL if the item belongs at the head of the list.
*************************************************/
template <class ItemType>
node<ItemType>* WhereThisGoes(node<ItemType>* head, ItemType value);

/*************************************************
* At:
*  Takes a position (n) and returns a pointer to the nth position in the list
* pre:
*  take a position (n)
* post:
*  returns a pointer to the nth position in the list
*************************************************/
template <class ItemType>
node<ItemType>* at(node<ItemType>* head, int n);

template <class ItemType>
int count(node<ItemType>* head);

template <class ItemType>
node<ItemType>* previous(node<ItemType>* head, node<ItemType>* beforeMe) {
    if (beforeMe == head)
        return NULL;
    else {
        node<ItemType>* before = head;
        while (before) {
            if (before->next == beforeMe)
                break;
            else
                before = before->next;
        }
        return before;
    }
}

template <class ItemType>
node<ItemType>* search(const ItemType &key, node<ItemType>* head) {
    node<ItemType>* walker = head;
    while (walker) {
        if (walker->item == key)
            return walker;
        else
            walker = walker->next;
    }
    return NULL;
}

template <class ItemType>
void insertHead(const ItemType& insertMe, node<ItemType>* &head) {
    node<ItemType>* newNode;
    newNode = new node<ItemType>;

    newNode->item = insertMe;
    newNode->next = head;
    head = newNode;
}

template <class ItemType>
node<ItemType>* insertAfter(const ItemType& insertMe, node<ItemType>* afterMe) {
    node<ItemType>* newNode;
    newNode = new node<ItemType>;
    newNode->item = insertMe;
    newNode->next = afterMe->next;
    afterMe->next = newNode;
    return newNode;
}

template <class ItemType>
node<ItemType>* insertBefore(node<ItemType>* &head, const ItemType &insertMe, node<ItemType>* beforeMe) {
    node<ItemType>* after;
    if (beforeMe == head) {
        insertHead(insertMe, head);   //change head
        return head;
    }
    else {
        after = previous(head, beforeMe);
        return insertAfter(insertMe, after);
    }
}

template <class ItemType>
node<ItemType>* insert(node<ItemType>* &head, const ItemType &insertMe){
    if(head){
        node<ItemType>* walker=head;
        while(walker->next){
            walker=walker->next;
        }
        walker->next=new node<ItemType>;
        walker->next->item=insertMe;
        walker->next->next=NULL;
    }
    else
        insertHead(insertMe,head);
}

template <class ItemType>
ItemType deleteNode(node<ItemType>* head, node<ItemType>* deleteMe) {
    ItemType temp = deleteMe->item;

    delete removeNode(head, deleteMe);;
    return temp;
}

template <class ItemType>
ItemType deleteHead(node<ItemType>* &head) {
    ItemType temp = head->item;
    delete removeHead(head);
    return temp;
}

template <class ItemType>
node<ItemType>* removeNode(node<ItemType>* head, node<ItemType>* removeMe)
{
    if (head == removeMe)
        return removeHead(head);
    else{
        node<ItemType>* before = previous(head, removeMe);
        before->next = removeMe->next;
        return removeMe;
    }
}

template <class ItemType>
node<ItemType>* removeHead(node<ItemType>* &head) {
    if (head) {
        node<ItemType>* temp = head;
        head = head->next;
        return temp;
    }
    else
        return NULL;
}

template <class ItemType>
void deleteAll(node<ItemType>* &head) {
    if (head) {
        while (head->next) {
            deleteNode(head, head->next);
        }
        delete head;
        head = NULL;
    }
}

template <class ItemType>
node<ItemType>* copy(node<ItemType>* sourceHead) {
    node<ItemType>* newHead = NULL;
    if (sourceHead == NULL)
        return newHead;
    else {
        node<ItemType>* walkerSource = sourceHead;
        insertHead(sourceHead->item, newHead);  //the first node
        node<ItemType>* walkerNew = newHead;
        ItemType nodeItem;
        while (walkerSource->next) {
            walkerSource = walkerSource->next;
            nodeItem = walkerSource->item;
            walkerNew = insertAfter(nodeItem,walkerNew);
        }
        return newHead;
    }
}

template <class ItemType>
void print(node<ItemType>* head, ostream &out) {
    while (head) {
        out << head->item << ' ';
        head = head->next;
    }
}

template <class ItemType>
node<ItemType>* WhereThisGoes(node<ItemType>* head, ItemType value) {
    node<ItemType>* me = search(value, head);
    return (previous(head, me) == NULL) ? head : previous(head, me);
}

template <class ItemType>
node<ItemType>* at(node<ItemType>* head, int n) {
    node<ItemType>* walker = head;
    for (int i = 1; i<n; i++) {
        walker = walker->next;
    }
    return walker;
}

template <class ItemType>
int count(node<ItemType>* head) {
    if (!head) {
        return 0;
    }
    else {
        int n = 1;
        node<ItemType>* walker = head;
        if (!walker) {
            return n;
        }
        while (walker->next) {
            walker = walker->next;
            n++;
        }
        return n;
    }
}



#endif // THENODE
