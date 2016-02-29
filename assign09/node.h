/*******************************************************************
 *
 *     FILE: node.h
 *
 *  PURPOSE: Contains the class definition of a Node
 *
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
     void setData(int item);   // --- stores item in data member of current node
     void setNext(Node* node); // --- sets next to point to node
};
