#ifndef H_UnorderedLinkedList
#define H_UnorderedLinkedList

//***********************************************************
// Author: D.S. Malik
//
// This class specifies the members to implement the basic
// properties of an unordered linked list. This class is
// derived from the class linkedListType.
//***********************************************************

#include "linkedList.h"

using namespace std;

template <class Type>
//class unorderedLinkedList: public linkedListType<Type>
class unorderedLinkedList: public linkedListType<int>
{
public:
    bool search(const Type& searchItem) const;
      //Function to determine whether searchItem is in the list.
      //Postcondition: Returns true if searchItem is in the list,
      //    otherwise the value false is returned.

    void insertFirst(const Type& newItem);
      //Function to insert newItem at the beginning of the list.
      //Postcondition: first points to the new list, newItem is
      //    inserted at the beginning of the list, last points to
      //    the last node, and count is incremented by 1.
      //

    void insertLast(const Type& newItem);
      //Function to insert newItem at the end of the list.
      //Postcondition: first points to the new list, newItem is
      //    inserted at the end of the list, last points to the
      //    last node, and count is incremented by 1.

    void deleteNode(const Type& deleteItem);
      //Function to delete deleteItem from the list.
      //Postcondition: If found, the node containing deleteItem
      //    is deleted from the list. first points to the first
      //    node, last points to the last node of the updated
      //    list, and count is decremented by 1.

    // ===== NEW FUNCTIONS ADDED =====
    bool deleteMinOnce();                 // delete first occurrence of smallest element
    int  deleteAll(const Type& item);     // delete all occurrences of a value
    Type kthElement(int k) const;         // return info at kth position
    bool deleteKth(int k);                // delete kth element
    void rotate();                        // move first node to end
    // =================================
};


template <class Type>
bool unorderedLinkedList<Type>::
                   search(const Type& searchItem) const
{
    nodeType<Type> *current; //pointer to traverse the list
    bool found = false;

    current = first; //set current to point to the first
                     //node in the list

    while (current != NULL && !found)    //search the list
        if (current->info == searchItem) //searchItem is found
            found = true;
        else
            current = current->link; //make current point to
                                     //the next node
    return found;
}//end search

template <class Type>
void unorderedLinkedList<Type>::insertFirst(const Type& newItem)
{
    nodeType<Type> *newNode; //pointer to create the new node

    newNode = new nodeType<Type>; //create the new node

    newNode->info = newItem;    //store the new item in the node
    newNode->link = first;      //insert newNode before first
    first = newNode;            //make first point to the
                                //actual first node
    count++;                    //increment count

    if (last == NULL)   //if the list was empty, newNode is also
                        //the last node in the list
        last = newNode;
}//end insertFirst

template <class Type>
void unorderedLinkedList<Type>::insertLast(const Type& newItem)
{
    nodeType<Type> *newNode; //pointer to create the new node

    newNode = new nodeType<Type>; //create the new node

    newNode->info = newItem;  //store the new item in the node
    newNode->link = NULL;     //set the link field of newNode
                              //to NULL

    if (first == NULL)  //if the list is empty, newNode is
                        //both the first and last node
    {
        first = newNode;
        last = newNode;
        count++;        //increment count
    }
    else    //the list is not empty, insert newNode after last
    {
        last->link = newNode; //insert newNode after last
        last = newNode; //make last point to the actual
                        //last node in the list
        count++;        //increment count
    }
}//end insertLast


template <class Type>
void unorderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    bool found;

    if (first == NULL)    //Case 1; the list is empty.
        cout << "Cannot delete from an empty list."
             << endl;
    else
    {
        if (first->info == deleteItem) //Case 2: the node to be deleted is the first node
        {
            current = first;
            first = first->link;
            count--;
            if (first == NULL)    //the list has only one node
                last = NULL;
            delete current;
        }
        else //search the list for the node with the given info
        {
            found = false;
            trailCurrent = first;  //set trailCurrent to point
                                   //to the first node
            current = first->link; //set current to point to
                                   //the second node

            while (current != NULL && !found)
            {
                if (current->info != deleteItem)
                {
                    trailCurrent = current;
                    current = current-> link;
                }
                else
                    found = true;
            }//end while

            if (found) //Case 3; if found, delete the node
            {
                trailCurrent->link = current->link;
                count--;

                if (last == current)   //node to be deleted
                                       //was the last node
                    last = trailCurrent; //update the value
                                         //of last
                delete current;  //delete the node from the list
            }
            else
                cout << "The item to be deleted is not in "
                     << "the list." << endl;
        }//end else
    }//end else
}//end deleteNode


// ======================
// ADDED FUNCTION BODIES
// ======================

template <class Type>
bool unorderedLinkedList<Type>::deleteMinOnce() {
    if (first == NULL) return false;

    nodeType<Type>* minNode = first;
    nodeType<Type>* minPrev = NULL;

    nodeType<Type>* prev = first;
    nodeType<Type>* curr = first->link;

    while (curr != NULL) {
        if (curr->info < minNode->info) {
            minNode = curr;
            minPrev = prev;
        }
        prev = curr;
        curr = curr->link;
    }

    if (minPrev == NULL) {
        first = minNode->link;
        if (last == minNode) last = first;
    } else {
        minPrev->link = minNode->link;
        if (last == minNode) last = minPrev;
    }

    delete minNode;
    count--;
    if (count == 0) last = NULL;
    return true;
}

template <class Type>
int unorderedLinkedList<Type>::deleteAll(const Type& item) {
    int removed = 0;
    nodeType<Type> dummy;
    dummy.link = first;

    nodeType<Type>* prev = &dummy;
    nodeType<Type>* curr = first;

    while (curr != NULL) {
        if (curr->info == item) {
            prev->link = curr->link;
            nodeType<Type>* del = curr;
            curr = prev->link;
            if (del == last) last = (prev == &dummy ? NULL : prev);
            delete del;
            count--;
            removed++;
        } else {
            prev = curr;
            curr = curr->link;
        }
    }

    first = dummy.link;
    if (count == 0) last = NULL;
    return removed;
}

#include <cstdlib>
#include <iostream>

template <class Type>
Type unorderedLinkedList<Type>::kthElement(int k) const {
    if (k <= 0 || k > count) {
        cerr << "kthElement: invalid k=" << k
             << " for list size " << count << ". Terminating.\n";
        exit(1);
    }

    nodeType<Type>* curr = first;
    for (int i = 1; i < k; ++i) curr = curr->link;
    return curr->info;
}

template <class Type>
bool unorderedLinkedList<Type>::deleteKth(int k) {
    if (k <= 0 || k > count) {
        cout << "deleteKth: invalid k=" << k
             << " for list size " << count << ".\n";
        return false;
    }

    if (k == 1) {
        nodeType<Type>* del = first;
        first = first->link;
        if (last == del) last = first;
        delete del;
        count--;
        if (count == 0) last = NULL;
        return true;
    }

    nodeType<Type>* prev = first;
    for (int i = 2; i < k; ++i) prev = prev->link;
    nodeType<Type>* del = prev->link;
    prev->link = del->link;
    if (last == del) last = prev;
    delete del;
    count--;
    return true;
}

template <class Type>
void unorderedLinkedList<Type>::rotate() {
    if (first == NULL || first->link == NULL) return;

    nodeType<Type>* oldHead = first;
    first = first->link;
    last->link = oldHead;
    last = oldHead;
    last->link = NULL;
}

#endif
