/******************************************************************************
* Program:
*    Assignment 10, Linked List implementation
*    Brother Ercanbrack, CS 235
* Author:
*    Tyler Scott
* Summary:
*  
*  
*
*  Estimated time: 8.0hrs
*  Actual time: 2+.0hrs
******************************************************************************/
   
/******************************************************************************
*
*     FILE: list.h
*
*  PURPOSE: Contains the class definition of a Node and a List
*
******************************************************************************/

using namespace std;
#include <iostream>
#include <cstdlib>

/******************************************************************************
* Node class definition for building a single linked list of integers.
******************************************************************************/
class Node
{
   private:
      int data;                 // --- data in each node
      Node* next;               // --- pointer to next node

   public:
      Node();                   // --- Creates empty node
      Node* getNext();          // --- returns next pointer of a node
      int getData();            // --- returns data of a node
      void setData(int item);   // --- stores item in data member of current
                                //     node
      void setNext(Node* node); // --- sets next to point to node
};

/******************************************************************************
* This class provides a dynamically allocated linked list implementation
* of a general list. It includes functions for creating, copying, and
* destroying a linked list data structure. It includes functions for inserting,
* removing, and retrieving data anywhere in the linked list data structure.
******************************************************************************/
class List
{
   private:
      int numItems;
      Node* firstNode;

   public:
      List();
      ~List();                      // destructor - free the entire linked list
      List(const List &listToCopy);    // copy constructor
      List& operator = (const List &rightSide);
      void insert(int item, int pos);  // insert item at the specified position
      void remove(int pos);            // remove item at the specified position
      int lookup(int item) const;   // returns position of item (zero relative)
      int getData(int pos) const;   // returns data located at the position
      int empty(void) const;       // check for empty list(0=empty 1=not empty)
      int getNumItems(void) const;     // return # of items in the linked list
};

// Node Member Functions

/******************************************************************************
 * Default constructor needs to be totally empty so it can work with stuff
 *****************************************************************************/
Node :: Node()                   // --- Creates empty node
{
}

/******************************************************************************
 * Grants access to the private variable "next"
 *****************************************************************************/
Node* Node :: getNext()
{
   return next; // --- returns next pointer of a node
}

/******************************************************************************
 * Grants access to the private variable "data"
 *****************************************************************************/
int Node :: getData()
{
   return data; // --- returns data of a node
}

/******************************************************************************
 * Sets the value of Data to what is passed in through the parameters
 *****************************************************************************/
void Node :: setData(int item)
{
   data = item; // --- stores item in data member of current node
}

/******************************************************************************
 * Sets the value of "next" to what is passed in through the parameters
 *****************************************************************************/
void Node :: setNext(Node* node)
{
   next = node; // --- sets next to point to node
}

// List Member Functions

/******************************************************************************
 * Default Constructor
 *****************************************************************************/
List :: List()
{
   numItems = 0;
   firstNode = NULL;
}

/******************************************************************************
 * Destructor
 *****************************************************************************/
List :: ~List()
{
   while (firstNode != NULL)
   {
      delete[] firstNode;
      firstNode = firstNode->getNext();
   }
   firstNode = NULL;
}

/******************************************************************************
 * Copy Constructor
 *****************************************************************************/
List :: List(const List &listToCopy)
{
}

/******************************************************************************
 * Assignment Operator
 *****************************************************************************/
List& List :: operator = (const List &rightSide)
{
}

/******************************************************************************
 * The insert function puts things (nodes) into the list. in the right places
 *****************************************************************************/
void List :: insert(int item, int pos)
{
   // Set up some new nodes
   Node* stuff = new Node();
   Node* curr = firstNode;
   stuff->setData(item); // set one of them with the data passed in

   // check to make sure its not the first position, or if the list is empty
   if (pos < 1 || firstNode == NULL) 
   {
      stuff->setNext(curr); // set the next node as the current one
      firstNode = stuff; 
   }
   else
   {
      for (int i = 0; i < numItems - 1; i++)
      {
         if (i == pos) // if there is already something there break out
            break;
         curr = curr->getNext(); // set the current node to point to the next 
      }
      stuff->setNext(curr->getNext()); // set the next node
   }   
}

/******************************************************************************
 * text
 *****************************************************************************/
void List :: remove(int pos)
{
}

/******************************************************************************
 * The lookup function walks through the list to check if a specific item
 * is located in the list.
 *****************************************************************************/
int List :: lookup(int item) const
{
   Node* search = firstNode; // set up a temporary node to search with
   for (int i = 0; i < numItems; i++) 
   {
      if (search->getData() == item) // if the search matches an item return
         return;
      search = search->getNext(); // set to the next node and keep looping
   }
   return -1; // it was not in the list
}

/******************************************************************************
 * text
 *****************************************************************************/
int List :: getData(int pos) const
{
}

/******************************************************************************
 * Checks to see if the list is empty 
 *****************************************************************************/
int List :: empty(void) const
{
   if (firstNode == NULL) // if the first node is pointing to Null its empty
      return -1;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
int List :: getNumItems(void) const
{
   return numItems;
}

