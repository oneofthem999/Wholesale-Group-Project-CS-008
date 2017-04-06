#ifndef THELIST
#define THELIST

#include "thenode.h"

template <class ItemType>
class List
{
public:
    //ctr
    List();
    List(node<ItemType>* head);

    //big 3
    List(const List& other);
    ~List();
    const List& operator = (const List& RHS);

    //basic functions
    void InsertAfter(const ItemType &insertMe, node<ItemType>* afterMe);
    void InsertBefore(const ItemType &insertMe, node<ItemType>* beforeMe);
    void InsertHead(const ItemType &insertMe);
    void Insert(const ItemType &insertMe);
    void DeleteNode(node<ItemType>* deleteMe);
    void DeleteAll();
    void DeleteHead();
    node<ItemType>* At(int n);
    bool IsEmpty();
    void sort();

    node<ItemType>* begin();

    //friends
    template <class ItemTypeF>
    friend ostream &operator << (ostream &out, const List<ItemTypeF>& printMe);


private:
    node<ItemType>* headptr;
};

template <class ItemType>
List<ItemType>::List()
{
    headptr = NULL;
}

template <class ItemType>
List<ItemType>::List(node<ItemType>* head)
{
    headptr = head;
}

//big 3
template <class ItemType>
List<ItemType>::List(const List& other)
{
    if (headptr)
        DeleteAll();
    headptr = copy(other.headptr);
}

template <class ItemType>
List<ItemType>::~List()
{
    DeleteAll();
}

template <class ItemType>
const List<ItemType>& List<ItemType>::operator = (const List& RHS)
{
    if (headptr)
        DeleteAll();
    headptr = copy(RHS.headptr);
    return RHS;
}

//basic functions
template <class ItemType>
void List<ItemType>::InsertAfter(const ItemType &insertMe, node<ItemType>* afterMe)
{
    insertAfter(insertMe, afterMe);
}

template <class ItemType>
void List<ItemType>::InsertBefore(const ItemType &insertMe,
    node<ItemType>* beforeMe)
{
    insertBefore(headptr, insertMe, beforeMe);
}

template <class ItemType>
void List<ItemType>::InsertHead(const ItemType &insertMe)
{
    insertHead(insertMe, headptr);
}

template <class ItemType>
void List<ItemType>::Insert(const ItemType &insertMe)
{
    insert(headptr, insertMe);
}

template <class ItemType>
void List<ItemType>::DeleteHead()
{
    deleteHead(headptr);
}

template <class ItemType>
void List<ItemType>::DeleteNode(node<ItemType>* deleteMe)
{
    deleteNode(headptr, deleteMe);
}

template <class ItemType>
void List<ItemType>::DeleteAll()
{
    deleteAll(headptr);
}

template <class ItemType>
node<ItemType>* List<ItemType>::At(int n)
{
    return at(headptr, n);
}

template <class ItemType>
bool List<ItemType>::IsEmpty()
{
    if (count(headptr) == 0)
        return true;
    else
        return false;
}

template <class ItemType>
void List<ItemType>::sort()
{
    node<ItemType> *ptr = headptr;
    ItemType tempItem;
    int size = 0;

    //Find the size of list
    while (ptr)
    {
        ptr = ptr->next;
        size++;
    }
    ptr = headptr;

    for (int j = 0; j < size; j++)
    {
        while (ptr->next)  //iterate through list until next is null
        {
            if (ptr->item > ptr->next->item)
            {
                tempItem = ptr->item;
                ptr->item = ptr->next->item;
                ptr->next->item = tempItem;
            }
            ptr = ptr->next;
        }
        ptr = headptr; //reset ptr
    }
}

template <class ItemType>
node<ItemType>* List<ItemType>::begin()
{
    return headptr;
}

#endif // THELIST
