/******************************************************************************
* Program:
*    Assignment 11, Hashing
*    Brother Ercanbrack, CS 235
* Author:
*    Tyler Scott
* Summary:
*    This program does hashing
*  
*  Estimated time: 5.0hrs
*  Actual time: 2.0hrs
******************************************************************************/
#include <iostream>
#include <fstream>
#include <list>
#include <string>
using namespace std;

/******************************************************************************
 * Index does the actual hashing.
 *****************************************************************************/
int index(string word)
{
   int x = 0; 
   for (int i = 0; i < word.length(); i++)
      x +=  word[i]; // add up to a sum
   return x % 67;  // then divide by 67 and keep the remainder
}

/******************************************************************************
 * Hashing pushes the indexed words onto the array
 *****************************************************************************/
void hashing(string word, list < string > * array)
{
   int y = index(word); // assign a holder for the indexed word
   array[y].push_back(word); // push it onto the array
}

/******************************************************************************
 * Iterates through the lists and displays properly
 *****************************************************************************/
void display(list < string > * array)
{

   for (int i = 0; i < 67; i++) // loop through to the end of the array
   {
      cout << "table[" << i << "]"; 
      if (i < 10) // if the position is less than 10, you need an extra space
      {
         cout << " -> "; // display with the extra space                
      }
      if (i >= 10)
      {
         cout << "-> ";                 
      }
   
      if (array[i].empty())  // check empty
         cout << "(empty)" << endl;
      else
      {
         for (list < string > ::iterator IT = array[i].begin();
              IT != array[i].end();)
         {
            // iterate through the list in the specified array location
            cout << *IT; // display the contents
            IT++; // move to the next position
            if (IT != array[i].end())
               cout << ", ";
           
         }
         cout << endl;
      }
   }
}

/******************************************************************************
 * Main is set up to read in the file and then call the necessary functions
 * to run the program
 *****************************************************************************/
int main(int argc, char* argv[])
{
   // declare a new array of lists
   list < string > array[67];

   // open the file from command line
   ifstream inFile;
   inFile.open(argv[argc - 1]);
   if (inFile.fail())
   {
      cout << "open file error " << argv[argc - 1] << endl;
      return 0;
   }

   // read in the information and store it as "word"
   string word;
   while (inFile >> word)
   {
      hashing(word, array); // pass it to the hashing function
   }
   display(array); // call the display
   return 0;
}

