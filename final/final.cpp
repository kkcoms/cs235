/******************************************************************************
* Program:
*    Assignment 256, Genealogy list tree beast
*    Brother Ercanbrack, CS 235
* Author:
*    Tyler Scott
* Summary: 
*
*
*   Estimated time: 8.0hrs
*   Actual time: 4.0hrs
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

/*****************************************************************************
 * Node class definition for building a single linked list of integers.
 *****************************************************************************/
template <typename T> class Node
{
   private:
      T data;                 // --- data in each node
      Node<T>* next;               // --- pointer to next node

   public:
      Node();                   // --- Creates empty node
      Node<T>* getNext();          // --- returns next pointer of a node
      T getData();            // --- returns data of a node
      void Node<T> :: insert(T item)
      void setData(T item);   // ---stores item in data member of current node
      void setNext(Node<T>* node); // --- sets next to point to node

};


class genInfo
{
   private:
      string firstName;
      string lastName;
      string birthday;
      string birthYear;
      string code;

   public:
      genInfo();
      string getFirst() const;
      void setFirst(string firstName);
      string getLast() const;
      void setLast(string lastName);
      string getBirth() const;
      void setBirth(string birthday);
      string getBYear() const;
      void setBYear(string birthYear);
      string getCode() const;
      void setCode(string code);
      bool operator < (const genInfo &rightSide);
};
   
/******************************************************************************
 * Default constructor needs to be totally empty so it can work with stuff
 *****************************************************************************/
template <typename T>
Node<T> :: Node()                   // --- Creates empty node
{
//   this->data = data;
}

/******************************************************************************
 * Grants access to the private variable "next"
 *****************************************************************************/
template <typename T>
Node<T>* Node<T> :: getNext()
{
   return next; // --- returns next pointer of a node
}

/******************************************************************************
 * Grants access to the private variable "data"
 *****************************************************************************/
template <typename T>
T Node<T> :: getData()
{
   return data; // --- returns data of a node
}

/******************************************************************************
 * Sets the value of Data to what is passed in through the parameters
 *****************************************************************************/
template <typename T>
void Node<T> :: setData(T item)
{
   data = item; // --- stores item in data member of current node
}

/******************************************************************************
 * Sets the value of "next" to what is passed in through the parameters
 *****************************************************************************/
template <typename T>
void Node<T> :: setNext(Node<T>* node)
{
   next = node; // --- sets next to point to node
}


/***********************************************************************
 * Main controls what happens
 ***********************************************************************/
T Node<T> :: insert(T item)
{
   genInfo record = item;
   Node<genInfo>* ptrHead = NULL;
   int numberIn; // holder for the variables read in

   while (fin >> numberIn) // keep looping while you have values to read
   {
      Node<genInfo>* node = new Node(); // setup a new node
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
   display(ptrHead); // call the display
   return 0;
}
/******************************************************************************
 * The insert function puts things (nodes) into the list. in the right places
 *****************************************************************************/
///NEED TO MODIFY IT
template <typename T>
void List<T> :: insert(T item)
{
   // cerr << "in insert\n";
   // check to make sure position is pointing within the list boundaries
   // Set up some new nodes
   Node<T>* stuff = new Node<T>(); 
   Node<T>* curr = firstNode;
   stuff->setData(item); // set one of them with the data passed in
   
   // check to make sure its not the first position, or if the list is empty
     if (empty())
     {
      firstNode = stuff;
      stuff->setNext(curr); // set the next node as the current one
      numItems++; // increment the number of items since adding one
      cout <<"inserted item as only item";
      return;
     }

     //head insert
     if (stuff->getData() < firstNode->getData())
      {
         stuff->setNext(firstNode); // set the next node
         numItems++; // increment the number of items since adding one   
         cout <<"inserted item as head";
         return;
      }
     
      //middle insert

     if (stuff->getData() < curr->getData())
     {
        stuff->setNext(curr->getNext()); // set the next node
        curr->setNext(stuff); // set the current node to the temp node
        numItems++; // increment the number of items since adding one
        cout <<"inserted item in middle";
        return;
     }
     //tail insert.
     //   if (curr->getData() < stuff->getData())
     //  {  
        curr->setNext(stuff); // set the current node to the temp node       
        numItems++; // increment the number of items since adding one
        cout <<"inserted item as end";
        return;
//     }
}



/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
genInfo :: genInfo()
{
   firstName = "_";
   lastName = "_";
   birthday = "_";
   birthYear = "_";
   code = "_";
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
string genInfo :: getFirst() const
{
   return firstName;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
void genInfo :: setFirst(string firstName)
{
   this->firstName = firstName;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
string genInfo :: getLast() const
{
   return lastName;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
void genInfo :: setLast(string lastName)
{
   this->lastName = lastName;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
string genInfo :: getBirth() const
{
   return birthday;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
void genInfo :: setBirth(string birthday)
{
   this-> birthday = birthday;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
string genInfo :: getBYear() const
{
   return birthYear;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
void genInfo :: setBYear(string birthYear)
{
   this-> birthYear = birthYear;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
string genInfo :: getCode() const
{
   return code;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
void genInfo :: setCode(string code)
{
   this->code = code;
}

/******************************************************************************
 * Grants access to the private variable "numItems"
 *****************************************************************************/
bool genInfo :: operator < (const genInfo &rightSide)
{
   cerr<< "in operator?\n";
   string tempA = this->lastName;
   string tempB = rightSide.getLast();
   tempA[0] = toupper(tempA[0]);
   tempB[0] = toupper(tempB[0]);
   if (tempA < tempB)
      return true;
   else if (tempA > tempB)
      return false;
   else
   {
      tempA = this->firstName;
      tempB = rightSide.getFirst();
      tempA[0] = toupper(tempA[0]);
      tempB[0] = toupper(tempB[0]);
      if (tempA < tempB)
         return true;
      else if (tempA > tempB)
         return false;
      else
      {
         tempA = this->birthYear;
         tempB = rightSide.getBYear();
         if (tempA < tempB)
            return true;
         else if (tempA > tempB)
            return false;
         else
         {
            tempA = this->birthday;
            tempB = rightSide.getBirth(); 
            if (tempA < tempB)
               return true;
            else if (tempA > tempB)
               return false;
         }
      }
   }
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


/******************************************************************************
 * Main controls what happens
 *****************************************************************************/
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
   string input;
   genInfo record;// = new genInfo();
   Node<genInfo> pedigree;// = new List<genInfo>();
   getline(fin, input); // get firstline
   while (!fin.eof())
   {
      if (input.substr(2,2) == "@I") //new record
      {
         Node<genInfo>* node = new Node<genInfo>();
         genInfo temp;// = new genInfo(); //make new record
         temp = record;
         pedigree.insert(temp);  //save old/previos record
         record.setCode(input.substr(4,1));
      }
      if (input.substr(2,4) == "SURN") //surname
         record.setLast(input.substr(7, input.length()));
      
      if (input.substr(2,4) == "GIVN") //given name
         record.setFirst(input.substr(7, input.length()));
      
      if (input.substr(2,4) == "BIRT") //birth date
      {
         getline(fin, input);
         if (input.substr(2,4) == "DATE")
         {
            record.setBirth(input.substr(7, input.length()));
            //  if (input.find("/") != string::npos)
            //  record.setBYear(input.substr(7, input.length()));
            //else
            //   record.setBYear(input.substr(13, input.length())); 
            //getting the year as a seperate integer makes sorting
            // easier
        }
      }    
      getline(fin, input);
      cout << "entries: " << pedigree.getNumItems();
      cout << "index code: " << record.getCode() << endl;
      cout << "name: " << record.getLast() << ", "
           << record.getFirst() << endl;
      cout << "date of birth: "<< record.getBirth() << " year: "
           << record.getBYear() << endl;

   }  
   fin.close(); // close the file
   genInfo testA;
   testA.setLast("Hartley");
   testA.setFirst("Marc");
   testA.setCode("1");
   testA.setBirth("06 Mar 1988");
   testA.setBYear("1988");

   genInfo testB;
   testB.setLast("Scott");
   testB.setFirst("Tyler");
   testB.setCode("2");
   testB.setBirth("30 Oct 1991");
   testB.setBYear("1991");

   List<genInfo> testC;
   testC.insert(testA);
   testC.insert(testB);  

   genInfo temp;
   for(int i = 0; i < 20; i++)
   {
      temp = pedigree.getData(i);
      cout << "index code: " << temp.getCode() << endl;
      cout << "name: " << temp.getLast() << ", "
           << temp.getFirst() << endl;
      cout << "date of birth: "<< temp.getBirth() << " year: "
           << temp.getBYear() << endl;
   }

   return 0;
}


