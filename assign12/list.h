/******************************************************************************
*
*     FILE: list.h
*
*  PURPOSE: Contains the class definition of a Node and a List
*
*******************************************************************************/
#ifndef _LIST_H
#define _LIST_H

using namespace std;
#include <iostream>
#include <cstdlib>


/*****************************************************************************
* Node class definition for building a single linked list of integers.
*****************************************************************************/
class Node
{
   private:
      int data;                 // --- data in each node
      Node* next;               // --- pointer to next node

   public:
      Node();                   // --- Creates empty node
      Node* getNext();          // --- returns next pointer of a node
      int getData();            // --- returns data of a node
      void setData(int item);   // --- stores item in data member of current node
      void setNext(Node* node); // --- sets next to point to node
};

/**********************************************************************************
* This class provides a dynamically allocated linked list implementation of a
* general list. It includes functions for creating, copying, and destroying a
* linked list data structure. It includes functions for inserting, removing,
* and retrieving data anywhere in the linked list data structure.
**********************************************************************************/
class List
{
   private:
      int numItems;
      Node* firstNode;

   public:
      List();
      ~List();                       // destructor - free the entire linked list 
      List(const List &listToCopy);  // copy constructor
      List& operator = (const List &rightSide);
      void insert(int item, int pos); // insert item at the specified position
      void remove(int pos);          // remove item at the specified position
      int lookup(int item) const;    // returns position of item (zero relative)
      int getData(int pos) const;    // returns data located at the position
      int empty(void) const;         // check for empty list(0=empty 1=not empty)
      int getNumItems(void) const;   // return # of items in the linked list
};
#endif
