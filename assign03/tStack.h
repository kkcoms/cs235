/************************************************************
*
*  NAME: Brother Ercanbrack
*  PROGRAM: stack.h
*  PURPOSE: Class definition for a stack object
*
************************************************************/
#ifndef STACK_H
#define STACK_H

using namespace std;
#include <iostream>
#include <cstdlib>

template <class T>
class Stack
{
   private:
     int myTop;                  // index of top of stack
     int maxSize;                // maximum size of stack  
     T *stackItems;            // pointer for dynamic array
   public:
     Stack(int size = 100);      // default constructor (stack size 100)
     Stack(const Stack<T> &aStack); // copy constructor 
     T top(void);              // returns the value of top item in the stack
     void push(int item);        // store item on the stack
     void pop(void);             // remove/delete top item off stack
     bool empty(void);           // is stack empty
     bool full(void);            // is stack full
     ~Stack();                   // destructor
     Stack<T>& operator = (const Stack<T> &rtSide); // overloaded assignment operator
};
#endif
