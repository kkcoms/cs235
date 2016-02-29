/******************************************************************************
* Program:
*    Assignment 15, HUFFMAN CODING
*    Brother Ercanbrack, CS 235
* Author:
*    Tyler Scott
* Summary:
* read into a list of BTree nodes, sorted smallest to largest, and then pop off
* two, assign left and right childs, their sum is the parent, push the parent
* back on the list. repeat.
*
*  Estimated time: 8.0hrs
*  Actual time: 8.0hrs
******************************************************************************/
#include <iostream>
#include <fstream>
#include <list>
using namespace std;

/*****************************************************************************
 * BTree class definition
 *****************************************************************************/
class BTree
{
   private:
      int data;          // --- data stored in node of tree
      BTree* left;       // --- pointer to left subtree
      BTree* right;      // --- pointer to right subtree
      BTree* parent;     // --- pointer to the parent node;
      char letter;       // --- letter stored in the node of a tree
   
   public:
      BTree(int data = 0);
      BTree(int data, char letter);  
      ~BTree(void);
      void insertLeft(int item); // creates a new node and inserts node to left
      void insertRight(int item);// creates a new node and inserts node to right
      BTree* getLeftChild(void);     // return the ptr to the left child
      BTree* getRightChild(void);    // return the ptr to the right child
      BTree* getParent(void);        // return parent
      int getData(void);
      void setData(int item);
      char getLetter(void);
      void setLetter(char item);
      void setLeft(BTree* tree);     
      void setRight(BTree* tree);
      void infix(void);              // do infix traversal
      void prefix(void);             // do prefix traversal
      void postfix(void);            // do postfix traversal
      void level(void);              // do level order traversal
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
 * Default BTree constructor
 *****************************************************************************/
BTree :: BTree(int data, char letter)
{
   this->data = data;
   left = NULL;
   right = NULL;
   parent = NULL;
   this->letter = letter;
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
 * grants access to "data"
 *****************************************************************************/
char BTree :: getLetter(void)
{
   return letter;
}

/*****************************************************************************
 * sets the value of data to what is passed in
 *****************************************************************************/
void BTree :: setData(int item)
{
   data = item;
}

/*****************************************************************************
 * sets the value of data to what is passed in
 *****************************************************************************/
void BTree :: setLetter(char item)
{
   letter = item;
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

     
/******************************************************************************
 *Encodes the Huffman Code
 *****************************************************************************/
void encode(string table[], BTree* tree, string code)
{
          
   if (!tree->getLeftChild() && !tree->getRightChild())//tree is a leaf 
   {
      // add code to table
      table[tree->getLetter()-'a'] = code;
      
   }
   else
   {
      encode(table, tree->getRightChild(), code + '0');
      encode(table, tree->getLeftChild(), code + '1');
   }
   
}

/**********************************************************************
 * Locates the 2 smallest letter frequencies
 *********************************************************************/
void findLeast(BTree *trees[], int &least1, int &least2)
{
   // smallest letter frequency
   for (int i = 0; i < 26; i++)
   {
      if (!trees[least1])
      {
         least1 = i;
      }
      else if (trees[i]
               && trees[least1]->getData() > trees[i]->getData())
      {
         least1 = i;
      }
   }

   // next smallest letter frequency
   for (int i = 0; i < 26; i++)
   {
      if (!trees[least2])
      {
         least2 = i;
      }
      else if (trees[i]
               && trees[least2]->getData() > trees[i]->getData()
               && i != least1)
      {
         least2 = i;
      }

   }
}

/******************************************************************************
 * Builds the huffman Tree
 *****************************************************************************/
BTree *createH(BTree* trees[])
{
   BTree *huff;
   int temp1;
   int temp2;

   for (int i = 0; i < 26 - (1 + 26 % 2); i++)
   {
      temp1 = 0;
      temp2 = 0;

      //find the least number frequency
      findLeast(trees, temp1, temp2);

      huff = new BTree();

      //assign the children and parent nodes
      huff->setData(trees[temp1]->getData() +
                    trees[temp2]->getData());
      huff->setLeft(trees[temp1]);
      huff->setRight(trees[temp2]);


      trees[temp1] = huff;
      trees[temp2] = NULL;
   }

   return huff;
}


/******************************************************************************
 * Main is set up to read in the file and then call the necessary functions
 * to run the program
 *****************************************************************************/
int main(int argc, char* argv[])
{
   string table[26];
   BTree *nodes[26];
   BTree *root;
 
   int freq = 0;

   // open the file from command line
   ifstream fin;
   fin.open(argv[argc - 1]);
   if (fin.fail())
   {
      cout << "open file error " << argv[argc - 1] << endl;
      return 0;
   }

  
   // read in the information and store it as BTree nodes
   for (int i = 0; fin >> freq; i++)
   {
      nodes[i] = new BTree(freq, i + 'a');
   }
   fin.close();

   root = createH(nodes);
   encode(table, root, "");

   //display the information
   for (int i = 0; i < 26; i++)
   {
      cout << char(i + 'a') << " = " << table[i] << endl;
   }
   
   return 0;
}
