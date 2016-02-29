#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

/****************************************************************************
* Template class for building a node object.  The data for the node can be
* any datatype.  
****************************************************************************/
template <class T>
class Node
{
   public:
      Node(const T &theData, Node<T>* theLink)
      : data(theData), link(theLink)
      {
         // left blank intentionally
      }
      Node<T>* getLink( )    { return link; }
      T& getData( )          { return data; }
      void setData(const T &theData) { data = theData; }
      void setLink(Node<T>* pointer) { link = pointer; }

   private:
      T data;            // The data object
      Node<T>* link;     // pointer to next node (i.e. link)
};

/****************************************************************************
* Desc: headInsert - creates a new node and inserts it at the beginning of
*       the linked list.
*
* Input: head - points to the first node in the linked list.
*        theData -  data object to be stored in the new node that is
*                   inserted at the beginning of the linked list.
* Output: head - points to the new first node in the linked list.
****************************************************************************/
template <class T>
void headInsert(Node<T>* &head, const T &theData)
{
   head = new Node<T>(theData, head);
}


/******************************************************************************
* Desc: insert - Creates new node (initializing it with "theData") and inserts
*       it in the linked list after the node pointed to by "afterMe".
*
* Input:  afterMe - pointer to node in the linked list to insert after.
*         theData - Data to be stored in the new node being inserted
* Output: afterMe - link is modified to point at inserted node
*         Note: if afterMe was Null when passed in, a head insert is done
*               and afterMe will now point at the inserted node, which is the
*               first node in the linked list.  
******************************************************************************/
template <class T>
void insert(Node<T>* &afterMe, const T &theData)
{
   if (afterMe != NULL)
   {
      afterMe->setLink(new Node<T>(theData, afterMe->getLink( )));
   }
   else
   {
      headInsert(afterMe,theData);
   }
}

#endif
