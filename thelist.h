#ifndef THELIST
#define THELIST

#include "thenode.h"

template <class ItemType>
class List
{
    public:
        class Iterator{
            public:
                friend class List;
                Iterator(){P=NULL;}

                Iterator(node<ItemType> *pointer){P=pointer;}

                void operator ++(ItemType){
                    if(P){
                        P=P->next;
                    }
                }

                ItemType& operator *(){
                    return P->item;
                }

                void operator [](int pos){
                    for(int i=0; i<pos; i++){
                        if(P)
                            P=P->next;
                    }
                }

                bool operator==(Iterator other){
                    if(P==other.P)
                        return true;
                    else
                        return false;
                }

                bool operator!=(Iterator other){
                    if(P!=other.P)
                        return true;
                    else
                        return false;
                }
            private:
                node<ItemType>* P;
            };

        //ctr
        List();
        List(node<ItemType>* head);

        //big 3
        List(const List& other);
        ~List();
        const List& operator = (const List& RHS);

        //basic functions
        List<ItemType>::Iterator InsertAfter(const ItemType &insertMe,
                                             List<ItemType>::Iterator afterMe);
        List<ItemType>::Iterator InsertBefore(const ItemType &insertMe,
                                              List<ItemType>::Iterator beforeMe);
        List<ItemType>::Iterator Search(const ItemType &key);
        void InsertHead(const ItemType &insertMe);
        ItemType DeleteNode(Iterator deleteMe);
        void DeleteAll();
        List<ItemType>::Iterator RemoveHead();
        ItemType DeleteHead();
        List<ItemType>::Iterator At(int n);
        bool IsEmpty();
        void sort();

        List<ItemType>::Iterator begin();
        List<ItemType>::Iterator end();

        //friends
        template <class ItemTypeF>
        friend ostream &operator << (ostream &out,
                                     const List<ItemTypeF>& printMe);

//    Selection Sort, Merge (of two sorted lists), UniqueMerge,
//    SplitList, AddLists, Subtract Lists.
    private:
        node<ItemType>* headptr;
};

template <class ItemType>
List<ItemType>::List()
{
    headptr=NULL;
}

template <class ItemType>
List<ItemType>::List(node<ItemType>* head)
{
    headptr=head;
}

//big 3
template <class ItemType>
List<ItemType>::List(const List& other)
{
    if(headptr)
        DeleteAll();
    headptr=copy(other.headptr);
}

template <class ItemType>
List<ItemType>::~List()
{
    DeleteAll();
}

template <class ItemType>
const List<ItemType>& List<ItemType>::operator = (const List& RHS)
{
    if(headptr)
        DeleteAll();
    headptr=copy(RHS.headptr);
    return RHS;
}

//basic functions
template <class ItemType>
typename List<ItemType>::Iterator
List<ItemType>::InsertAfter(const ItemType &insertMe,
                            List<ItemType>::Iterator afterMe)
{
    node<ItemType>* after=afterMe.P;
    after =insertAfter(insertMe, after);
    return Iterator (after);
}

template <class ItemType>
typename List<ItemType>::Iterator
List<ItemType>::InsertBefore(const ItemType &insertMe,
                             List<ItemType>::Iterator beforeMe)
{
    node<ItemType>* before=beforeMe.P;
    before=insertBefore(headptr, insertMe, before);
    return Iterator (before);
}

template <class ItemType>
typename List<ItemType>::Iterator
List<ItemType>::Search(const ItemType &key)
{
    node<ItemType>* target= search(key,headptr);
    return Iterator(target);
}

template <class ItemType>
void List<ItemType>::InsertHead(const ItemType &insertMe)
{
    insertHead(insertMe, headptr);
}

template <class ItemType>
typename List<ItemType>::Iterator List<ItemType>::RemoveHead()
{
    node<ItemType>* re= removeHead(headptr);
    return Iterator(re);
}

template <class ItemType>
ItemType List<ItemType>::DeleteHead()
{
    return deleteHead(headptr);
}

template <class ItemType>
ItemType List<ItemType>::DeleteNode(Iterator deleteMe)
{
    node<ItemType>* del=deleteMe.P;
    del= deleteNode(headptr, deleteMe);
    return Iterator(del);
}

template <class ItemType>
void List<ItemType>::DeleteAll()
{
    deleteAll(headptr);
}

template <class ItemType>
typename List<ItemType>::Iterator List<ItemType>::At(int n)
{
    node<ItemType>* at=at(headptr,n);
    return Iterator(at);
}

template <class ItemType>
bool List<ItemType>::IsEmpty()
{
    if(count(headptr)==0)
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

    for (int j=0; j < size; j++)
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
typename List<ItemType>::Iterator List<ItemType>::begin()
{
    return Iterator(headptr);
}

template <class ItemType>
typename List<ItemType>::Iterator List<ItemType>:: end()
{
    return Iterator(NULL);
}


#endif // THELIST
