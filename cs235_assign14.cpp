/******************************************************************************
* Program:
*    Assignment 14, Binary Search Tree
*    Brother Ercanbrack, CS 235
* Author:
*    Tyler Scott
* Summary:
*    This program defines the member functions for the BTree search class
*
*  Estimated time: 8.0hrs
*  Actual time: 4.0hrs
******************************************************************************/

#include <iostream>
using namespace std;

/*****************************************************************************
 * BTree Class
 *****************************************************************************/
class BTree
{
private:
   int data;          // --- data stored in node of tree
   BTree* left;       // --- pointer to left subtree
   BTree* right;      // --- pointer to right subtree
   BTree* parent;     // --- pointer to the parent node

public:
   BTree(int data = 0);
   ~BTree(void);
   void insertLeft(int item);    // creates a new node and inserts node to left
   void insertRight(int item);  // creates a new node and inserts node to right
   BTree* getLeftChild(void);     // return the ptr to the left child
   BTree* getRightChild(void);    // return the ptr to the right child
   BTree* getParent(void);        // return parent
   int getData(void);
   void setData(int item);
   void setLeft(BTree* tree);
   void setRight(BTree* tree);
   void infix(void);              // do infix traversal
   void prefix(void);             // do prefix traversal
   void postfix(void);            // do postfix traversal
   void level(void);              // do level order traversal
};

/*****************************************************************************
 * BST Class
 *****************************************************************************/
class BST
{
private:
   BTree* root;

public:
   BST();
   int empty(void);
   BTree* search(int item);
   void insert(int item);
   void remove(int item);
   void BSTInfix(void);
};

/*****************************************************************************
 * Default BTree constructor
 *****************************************************************************/
BTree :: BTree(int data)
{
   this->data = data;
   left = NULL;
   right = NULL;
   parent = NULL;
}

/*****************************************************************************
 * Deconstructor left blank because it is not used
 *****************************************************************************/
BTree :: ~BTree(void)
{

}

/*****************************************************************************
 * Inserts a node on the left pointer of the current node
 *****************************************************************************/
void BTree :: insertLeft(int item)
{  
   BTree* insert = new BTree(item);
   left = insert;  
   insert->parent = this;
}

/*****************************************************************************
 * Inserts a node on the right pointer of the current node
 *****************************************************************************/
void BTree :: insertRight(int item)
{
   BTree* insert = new BTree(item);
   right = insert;
   insert->parent = this;
}

/*****************************************************************************
 * grants access to the private BTree node "left" 
 *****************************************************************************/
BTree* BTree :: getLeftChild(void)
{
   return left;
}

/*****************************************************************************
 * grants access to the private BTree node "right"
 *****************************************************************************/
BTree* BTree :: getRightChild(void)
{
   return right;
}

/*****************************************************************************
 * grants access to "parent"
 *****************************************************************************/
BTree* BTree :: getParent(void)
{
   return parent;
}

/*****************************************************************************
 * grants access to "data"
 *****************************************************************************/
int BTree :: getData(void)
{
   return data;
}

/*****************************************************************************
 * sets the value of data to what is passed in
 *****************************************************************************/
void BTree :: setData(int item)
{
   data = item;
}

/*****************************************************************************
 * sets left to the tree that is passed in
 *****************************************************************************/
void BTree :: setLeft(BTree* tree)
{
   left = tree;
   if (tree != NULL)
      left->parent = this;
}

/*****************************************************************************
 * sets the right to the tree that is passed in
 *****************************************************************************/
void BTree :: setRight(BTree* tree)
{
   right = tree;
   if (tree != NULL)
      right->parent = this;
}

/*****************************************************************************
 * left visit right traversal
 *****************************************************************************/
void BTree :: infix(void)
{
   if (left != NULL) left->infix();
   cout << data << " ";
   if (right != NULL) right->infix();
}

/*****************************************************************************
 * visit left right traversal
 *****************************************************************************/
void BTree :: prefix(void)
{
   cout << data << " ";
   if (left != NULL) left->prefix();
   if (right != NULL) right->prefix();
}

/*****************************************************************************
 * left right visit traversal
 *****************************************************************************/
void BTree :: postfix(void)
{
   if (left != NULL) left->postfix();
   if (right != NULL) right->postfix();
   cout << data << " ";
}

/*****************************************************************************
 * level order traversal.
 *****************************************************************************/
void BTree :: level(void)
{
 const int MAX = 50;
  BTree *queue[MAX];
  BTree *temp;
  int front = 0;
  int back = 0;

  queue[back++] = this;

  while (front != back)
  {
    temp = queue[front];
    front = (front + 1) % MAX;
    if (temp != NULL)
    {
      // visit
      cout.width(4);
      cout << temp->data << " ";
      if (temp->parent == NULL)
         cout << " Parent = NULL! " << endl;
      else
         cout << " Parent = " << temp->parent->data << "   " << endl;
      // end Visit        
      queue[back] = temp->left;
      back = (back + 1) % MAX;
      queue[back] = temp->right;
      back = (back + 1) % MAX;
    }
  }
}


/*****************************************************************************
 * Default BST constructor
 *****************************************************************************/
BST::BST()
{
   root = NULL;
}

/*****************************************************************************
 * Checks if the tree is empty
 *****************************************************************************/
int BST::empty(void)
{
   if (root == NULL)
     return 0;
   else
      return 1;
}

/*****************************************************************************
 * Search the Tree for the item
 *****************************************************************************/
BTree* BST::search(int item)
{
   BTree* z = root; // create a new temp tree
   bool found = false; 
   while (!found && z != 0) // loop while its not found
   {
      if (item < z->getData()) // if its less go left
         z = z->getLeftChild();
      else if (item > z->getData()) // if its greater go right
         z = z->getRightChild();
      else
         found = true; // you found it!
   }
   return z;
}

/*****************************************************************************
 * Inserts into the tree and sorts to the correct spots
 *****************************************************************************/
void BST::insert(int item)
{
 
   BTree* z = root; // temporary tree
   BTree* parent = NULL;
   bool found = false;

   //search to check where to insert
   while (!found && z != 0)
   {
      parent = z;
      if (item <= z->getData())
         z = z->getLeftChild();
      else if (item >= z->getData())
         z = z->getRightChild();
      else
         found = true;
   }
   
   // if inserting
   if (z == 0)
   {
      z = new BTree(item); // set up a new tree
      if (parent == 0)
         root = z;
      else if (item <= parent->getData())
      {
         parent->setLeft(z); //  insert right of parent
      }
      else if (item >= parent->getData())
      {
         parent->setRight(z); // insert left of parent
      }
   }
}

/*****************************************************************************
 * Removes from the tree from the correct spot
 *****************************************************************************/
void BST::remove(int item)
{
   BTree* z = search(item); // z is a temporary tree
   if (z == NULL)
   {
      cout << "Item " << item << " is not found, cannot delete it!\n";
      return;
   }
   if (z->getLeftChild() != 0 && z->getRightChild() != 0)
   {
      BTree* zSucc = z->getRightChild(); 
      while (zSucc->getLeftChild() != 0)
         zSucc = zSucc->getLeftChild();

      z->setData(zSucc->getData());
      z = zSucc;
   }
   BTree* subTree = z->getLeftChild();
   if (subTree == 0)
      subTree = z->getRightChild();
   if (z == 0)
      root = subTree;
   else if (z->getParent()->getLeftChild() == z)
      z->getParent()->setLeft(subTree);
   else
      z->getParent()->setRight(subTree);
   delete z;
}

/*****************************************************************************
 * Infix BST traversal
 *****************************************************************************/
void BST::BSTInfix(void)
{
   if (root != NULL) root->infix(); // call the BTREE infix 
}

