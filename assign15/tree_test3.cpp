/*************************************************************
 *
 *   NAME: Brother Ercanbrack
 *
 *   FILE: test3.cpp
 *
 *   PURPOSE: This program tests the setRight and setLeft
 *            functions of the binary tree class.
 *            It also tests the setRight to see if the
 *            parent is handled correctly, by pruning
 *            the tree by setting the roots right link to null
 *
 *************************************************************/
using namespace std;
#include <iostream>
#include <math.h>
#include "tree.h"

main()
{
   BTree *node[15];
   int array[] = {23, 15, 21, 29, 26, 27, 3, 10, 0, 2, 20, 9, 14, 22, 1};

   for (int i = 0; i < 15; ++i)
   {
      node[i] = new BTree(array[i]);
   }

   for (int i = 6; i >= 0; i--)
   {
      node[i]->setLeft(node[i*2+1]);
      node[i]->setRight(node[i*2+2]);
   }
   // prune off right branch - this nodes left child is null
   node[0]->setRight(node[14]->getLeftChild()); 
   
   cout << "Tree in Infix-Order Traversal" << endl;
   node[0]->infix();
   cout << endl;

   cout << "Tree in Prefix-Order Traversal" << endl;
   node[0]->prefix();
   cout << endl;

   cout << "Tree in Postfix-Order Traversal" << endl;
   node[0]->postfix();
   cout << endl;

   cout << "Tree in Level-Order Traversal" << endl;
   node[0]->level();
   cout << endl;

}
