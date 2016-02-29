/******************************************************************************
* Program:
*    Assignment 12, Fibbonacci Doubly Linked List implementation
*    Brother Ercanbrack, CS 235
* Author:
*    Tyler Scott
* Summary:
*  This program takes a number input by the user. and then adds all the numbers
*  in the fibonacci sequence up to that number
*
*  Estimated time: 8.0hrs
*  Actual time: 4.0hrs
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/*****************************************************************************
 * Node class definition for building a single linked list of integers.
 *****************************************************************************/
class Node
{
   private:
      int data;                 // --- data in each node
      Node* next;               // --- pointer to next node
      Node* previous;           // --- pointer to the previous node
   public:  
      Node();                   // --- Creates empty node
      Node* getNext();          // --- returns next pointer of a node
      Node* getPrevious();      // --- returns previous pointer of a node
      int getData();            // --- returns data of a node
      void setData(int item);   // ---stores item in data member of current node
      void setNext(Node* node); // --- sets next to point to node
      void setPrevious(Node* node); // --- sets previous to point to node
};

/*******************************************************************************
 * This class provides a dynamically allocated linked list implementation of a
 * general list. It includes functions for creating, copying, and destroying a
 * linked list data structure. It includes functions for inserting, removing,
 * and retrieving data anywhere in the linked list data structure.
 ******************************************************************************/
class List
{
   private:
      int numItems;
      Node* firstNode;

   public:
      List();
      ~List();                       // destructor - free the entire linked list
      List(const List &listToCopy);  // copy constructor
      List& operator = (const List &rightSide); // assignment operator overload
      List operator + (List &rightSide); // addition operator overload
      void insert(int item, int pos); // insert item at the specified position
      void remove(int pos);          // remove item at the specified position
      int lookup(int item) const;    // returns position of item (zero relative)
      int getData(int pos) const;    // returns data located at the position
      int empty(void) const;        // check for empty list(0=empty 1=not empty)
      int getNumItems(void) const;   // return # of items in the linked list
      void display();
};

// Node Member Functions

/******************************************************************************
 * Default constructor needs to be totally empty so it can work with stuff
 *****************************************************************************/
Node :: Node()                   // --- Creates empty node
{
   data = 0;
   next = NULL;
   previous = NULL;
}

/******************************************************************************
 * Grants access to the private variable "next"
 *****************************************************************************/
Node* Node :: getNext()
{
   return next; // --- returns next pointer of a node
}

/******************************************************************************
 * Grants access to the private variable "previous"
 *****************************************************************************/
Node* Node :: getPrevious()
{
   return previous; // --- returns previous pointer of a node
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

/******************************************************************************
 * Sets the value of "previous" to what is passed in through the parameters
 *****************************************************************************/
void Node :: setPrevious(Node* node)
{
   previous = node; // --- sets previous to point to node
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
 * Addition Operator
 *****************************************************************************/
List List :: operator + (List &rightSide)
{
   List sum; // new list for the sum
   int first; // first number
   int second; // second number
   int result; // result of their addition
   int carry = 0; // carry over 
   int i = 0;

   //loop through until you reach the size, which is the end
   while (i < numItems || i < rightSide.numItems)
   {
      if (i < numItems)
      {
         first = getData(i); // get the first number from the first list
      }
      else
         first = 0;
      
      if (i < rightSide.numItems)
      {
         second = rightSide.getData(i); // get the second number from the second
      }
      else
         second = 0;

      int temp = first + second + carry; // set up a temp to hold the sum of all
      result = temp % 100000000;
      carry = temp / 100000000;
      sum.insert(result, i); // insert the result into the sum list
      i++;
   }
   if (carry > 0) // if there is a carry insert that too.
      sum.insert(carry, i);
   return sum;
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
      stuff->setPrevious(NULL);
   }

   else
   {
      for (int i = 1; i < pos; i++)
      {
         curr = curr->getNext(); // set the current node to point to the next 
      }
      stuff->setNext(curr->getNext()); // set the next node
      stuff->setPrevious(curr); // set the previous node
      if (stuff->getNext())
         stuff->getNext()->setPrevious(stuff);
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
      remove->getNext()->setPrevious(curr);
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

/******************************************************************************
 * this is the display function, outputs to the screen for users
 *****************************************************************************/
void List::display()
{
   Node* disp = firstNode; //set up a new node to point to the first in the list
   while (disp->getNext() != NULL)
   {
      disp = disp->getNext(); // point to the next one
   }
   for (; disp!= NULL; disp = disp->getPrevious())
   {
      cout << disp->getData(); // display to the screen
   }
}

/******************************************************************************
 * Main executes the functions
 *****************************************************************************/
int main(int argc, char* argv[])
{
   int cmdIn; // integer from  command line
   if (argc == 2)
   {
      cmdIn = atoi(argv[argc - 1]);
   }
   else
   {
      cout << "error" << endl;
      return 0;
   }

   List fibNum1; // new list object for first number
   fibNum1.insert(1,0); // insert a 1 at position 0 (since you will be adding
                        // all the integers between 0 and the input number

   List fibNum2;  // new list object for second number
   fibNum2.insert(1,0);

   List fibNum3; // new list object for third number

   for (int i = 3; i <= cmdIn; i++)
   {
      fibNum3 = fibNum1 + fibNum2;  // add 1 and 2 for sum
      fibNum1 = fibNum2; // now set the original 1st to the second
      fibNum2 = fibNum3; // and set the second to the sum 
   }
   fibNum3.display();  // call display
   cout << endl << endl;
   return 0;
}
