/******************************************************************************
* Program:
*    Assignment 10, Linked List implementation
*    Brother Ercanbrack, CS 235
* Author:
*    Tyler Scott
* Summary:
*  this program implements the member functions of the list class
*  
*
*  Estimated time: 8.0hrs
*  Actual time: 5.0hrs
******************************************************************************/
#include <iostream>
#include "list.h"
using namespace std;
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
 * Destructor clears out the list
 *****************************************************************************/
List :: ~List()
{
   while (firstNode != NULL)
   {
      Node* deletor = firstNode;
      firstNode = firstNode->getNext();
      delete deletor;
   }
}

/******************************************************************************
 * Copy Constructor
 *****************************************************************************/
List :: List(const List &listToCopy)
{
   numItems = 0;
   firstNode = 0;
   
   for (int i = 0; i < listToCopy.numItems; i++)
   {
      insert(listToCopy.getData(i), i);
   }   
}

/******************************************************************************
 * Assignment Operator
 *****************************************************************************/
List& List :: operator = (const List &rightSide)
{
   while (firstNode != NULL)
   {
      Node* deletor = firstNode;
      firstNode = firstNode->getNext();
      delete deletor;
   }

   numItems = 0;
   firstNode = 0;
   
   for (int i = 0; i < rightSide.numItems; i++)
   {
      insert(rightSide.getData(i), i);
   }   
}

/******************************************************************************
 * The insert function puts things (nodes) into the list. in the right places
 *****************************************************************************/
void List :: insert(int item, int pos)
{
   // check to make sure position is pointing within the list boundaries
   if (pos < 0 || pos > numItems)
   {
      if (pos < 0)
         pos = 0;
      else
         pos = numItems;
   }
   
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
      for (int i = 1; i < pos; i++)
      {
         curr = curr->getNext(); // set the current node to point to the next 
      }
      stuff->setNext(curr->getNext()); // set the next node
      curr->setNext(stuff); // set the current node to the temp node
   }   
   numItems++; // increment the number of items since adding one
}

/******************************************************************************
 * Remove deletes an item in the specified position of the list
 *****************************************************************************/
void List :: remove(int pos)
{
   // check to make sure position is pointing within the list boundaries
   if (pos < 0 || pos > numItems)
   {
      if (pos < 0)
         pos = 0;
      else
         pos = numItems - 1;
   }
   
   Node* curr = firstNode;
   // check to make sure its not the first position, or if the list is empty
   if (pos < 1 || firstNode == NULL) 
   {
      firstNode = curr->getNext(); // point the first to the next
      delete curr; // delete the current one
   }

   else
   {
      for (int i = 1; i < pos; i++)
      {
         curr = curr->getNext(); // set the current node to point to the next 
      }
      Node* remove = curr->getNext(); // make a temp one set to the node being
                                      // removed
      curr->setNext(remove->getNext()); // set the next node to the temp ones
      delete remove; // delete it
   }   
   numItems--;  // decrement the number of items
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
         return i;
      search = search->getNext(); // set to the next node and keep looping
   }
   return -1; // it was not in the list
}

/******************************************************************************
 * Gets the Data from each node in the list
 *****************************************************************************/
int List :: getData(int pos) const
{
   if (pos < 0 || pos > numItems) // if the postion is pointing to outside 
      return -1;                  // the list boundaries end
   Node* temp = firstNode; // set up a temp holder
   for (int i = 0; i < pos; i++)
   {
      temp = temp->getNext(); // walk through the list, point to the next
   }
   return temp->getData(); // return the data recieved
}

/******************************************************************************
 * Checks to see if the list is empty 
 *****************************************************************************/
int List :: empty(void) const
{
   if (firstNode == NULL) // if the first node is pointing to Null its empty
      return 1;
   else
      return 0;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
int List :: getNumItems(void) const
{
   return numItems;
}

