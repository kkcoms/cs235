/***********************************************************************
* Program:
*    Assignment 09, Linked List implementation
*    Brother Ercanbrack, CS 235
* Author:
*    Tyler Scott
* Summary: 
*    This program reads in a bunch of integers from a file, sorts them
*    using a linked list and then displays them.
* Estimated time: 8.0hrs
* Actual time: 4.0hrs
***********************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

/*******************************************************************
 * FILE: node.h
 * PURPOSE: Contains the class definition of a Node
 *******************************************************************/
class Node
{
   private:
      int data;                 // --- data in each node
      Node* next;               // --- pointer to next node

   public:
      Node();                   // --- Creates empty node
      Node* getNext();          // --- returns next pointer of a node
      int getData();            // --- returns data of a node
      void setData(int item);   // --- stores item in data member of
                                //      current node
      void setNext(Node* node); // --- sets next to point to node
};

/***********************************************************************
 * Default constructor needs to be totally empty so it can work with stuff
 **********************************************************************/
Node :: Node()                   // --- Creates empty node
{
}

/***********************************************************************
 * Grants access to the private variable "next"
 ******************************************************************/
Node* Node :: getNext()
{
   return next; // --- returns next pointer of a node
}

/***********************************************************************
 * Grants access to the private variable "data"
 ******************************************************************/
int Node :: getData()
{
   return data; // --- returns data of a node
}

/***********************************************************************
 * Sets the value of Data to what is passed in through the parameters
 ******************************************************************/
void Node :: setData(int item)
{
   data = item; // --- stores item in data member of current node
}

/***********************************************************************
 * Sets the value of "next" to what is passed in through the parameters
 ******************************************************************/
void Node :: setNext(Node* node)
{
   next = node; // --- sets next to point to node
}

/***********************************************************************
 * Display the list of nodes
 ***********************************************************************/
void display(Node * &ptrH)
{
   int numberOut; // this is a holder for the variables you want to display
   int countWrapula = 0; // counter for the line length being output

   // here's where you traverse the list
   for (Node* ptrN = ptrH; ptrN != NULL; ptrN = ptrN->getNext())
   {    
      numberOut =  ptrN->getData(); // set the holder to the value returned
      cout << setw(3) <<  numberOut; // output
      countWrapula++; // increment the counter
      if (countWrapula % 20 == 0) // if the counter divides evenly by 20
         cout << endl;       // end the line
   }
}

/***********************************************************************
 * Main controls what happens
 ***********************************************************************/
int main(int argc, char** argv)
{
   // input the file from the command line
   string filename = "";
   if (argc == 2)
      filename = argv[1];
   else
      getline(cin, filename);

   // Opening the file
   ifstream fin;
   fin.open(filename.c_str()); // open the file
   if (fin.fail())
   {
      cout << "Error reading File...";
      return 0; // if the file cant open display error
   }

   // Set the head Node to Null
   Node* ptrHead = NULL;
   int numberIn; // holder for the variables read in

   while (fin >> numberIn) // keep looping while you have values to read
   {
      Node* node = new Node(); // setup a new node
      node->setData(numberIn); // put the input data in it
      
      if (ptrHead != NULL) // if the head node is pointing to null
      {
         Node* ptr = ptrHead; // set up a pointer to point previous

         // loop through till the next pointer is at Null
         for (Node* ptrNext = ptrHead; ptrNext != NULL;
             ptr = ptrNext, ptrNext = ptrNext->getNext())
         {
            // if the data is equal to the new one pointed at
            if (ptrNext == ptrHead && node->getData() < ptrNext->getData())
            {
               // sort it before the current pointed at
               node->setNext(ptrHead);
               ptrHead = node;
               break;              
            }
            // if the data is less than the next one
            if (node->getData() < ptrNext->getData())
            {
               // sort it before the next one
               node->setNext(ptrNext);
               ptr->setNext(node);
               break;
            }
            // if the next one is pointing at null
            if (ptrNext->getNext() == NULL)
            {
               // the next one is now the current one (get stuck or stop)
               ptrNext->setNext(node);
               node->setNext(NULL);
               break;
            }
         }
      }
      else
      {
         // otherwise the next one is the head
         node->setNext(ptrHead);
         ptrHead = node;         
      }   
   }
   fin.close(); // close the file
   display(ptrHead); // call the display
   return 0;
}



