/***********************************************************************
 * Program:
 *    Assignment 02, Stack Class Methods Integration
 *    Brother Ercanbrack, CS235
 * Author:
 *    Tyler Scott
 * Summary:
 *      This program is designed to utilize the provided stack class
 *      (stack.h). The task was to incorporate and write the member
 *      functions associated with it. It is designed to be tested with
 *      the other included .cpp files. It is designed that it can work
 *      with those files.
 *
 *    Estimated:  5.0 hrs
 *    Actual:     2.0 hrs
 *
 ************************************************************************/

#include <iostream>
using namespace std;
#include "stack.h"

//Methods for member functions listed below
/********************************************
 *Default Constructor
 ********************************************/
Stack::Stack(int size) // default constructor (stack size 100)
{
   if (size > 0);
   {
      myTop = 0;  
      maxSize = size;
      stackItems = new int[maxSize];
// as long as the passed in size is greater than 0, set up the array
// with the capacity that size.
      if (stackItems != 0)
         myTop =  -1;// when the array is at 0, the top is a position
                     // previous, aka -1.
      else
      {
         cerr<< "[Error: Not enough memory to allocate.]\n";
      }
   }
}

/********************************************
 *Copy Constructor
 ********************************************/
Stack::Stack(const Stack &aStack)// copy constructor
{
   myTop = aStack.myTop;//duplicates all the assigned variables to the
                        //new constructor for myTop, maxSize, and the
                        //array of stuff.
   maxSize = aStack.maxSize;
   stackItems = new int[aStack.maxSize];
   if (stackItems != 0)
   {
      for (int i = 0; i <= aStack.myTop; i++)
      {
         stackItems[i] = aStack.stackItems[i];
         //duplicate the array values individually.
      }
   }
}

/********************************************
 *Methods for member functions first
 ********************************************/
int Stack::top(void) // returns the value of top item in the stack
{
   if (!empty())
      return(stackItems[myTop]);
   else
   {
      cerr << "[Error: Stack is empty -- spewing garbage...]";
   }
}

/********************************************
 *Methods for member functions first
 ********************************************/
void Stack::push(int item)  // store item on the stack
{
   if (myTop < maxSize -1)// if the top is receded on position
   {
      ++myTop; //increment the top.
      stackItems[myTop] = item; //sets the top equal to the new
                                //passed in
   }
   else
   {
      cerr << "ERROR: Stack Overflow\n";
//      cerr << "[Error: Stack is full -- can't add a new item...]\n"
      //         << " Must increase the maximum capacity of the stack.\n";
      return;
   }
}

/********************************************
 *Methods for member functions first
 ********************************************/
void Stack::pop(void)       // remove/delete top item off stack
{
   if (!empty())
      myTop--;
   else
      cerr << "ERROR: Stack Underflow\n";
//      cerr << "[Error: Stack is empty -- cant remove items]\n";
}

/********************************************
 *Methods for member functions first
 ********************************************/
bool Stack::empty(void)    // is stack empty
{
   return (myTop==-1);
}

/********************************************
 *Methods for member functions first
 ********************************************/
bool Stack::full(void)     // is stack full
{
   return (maxSize == myTop + 1);
}

/********************************************
 *Methods for member functions first
 ********************************************/

Stack::~Stack()                   // destructor
{
   delete[] stackItems;
   stackItems = NULL;
}

/********************************************
 *Methods for member functions first
 ********************************************/
Stack& Stack::operator = (const Stack &rtSide) // overloaded assignment operator
{
   if (this != &rtSide)
   {
      if(maxSize != rtSide.maxSize)
      {
         delete[] stackItems;
         maxSize = rtSide.maxSize;
         stackItems =  new int[maxSize];
         if (stackItems == 0)
         {
            cerr << "[Error: Inadequate memory]\n";
         }
      }
      myTop = rtSide.myTop;
      for (int i = 0; i <= myTop; i++)
      {
         stackItems[i] = rtSide.stackItems[i];
      }
   }
   return *this;
}
  /* if(this == &rtSide)
   {
      return *this;
       }
   if(rtSide.myTop > maxSize)
   {
      delete[] stackItems;
      stackItems = new int[rtSide.maxSize];
      maxSize = rtSide.maxSize;
   }

   for(int i = 0; i < rtSide.myTop; i++)
   {
      stackItems[i] = rtSide.stackItems[i];
   }
   myTop = rtSide.myTop;
   return *this;
  */
//}
