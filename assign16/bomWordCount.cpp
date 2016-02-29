/******************************************************************************
* Program:
*    Assignment 16, BOM Word Count
*    Brother Ercanbrack, CS 235
* Author:
*    Tyler Scott
* Summary:
*   This program keeps track of the most repeated words in the Book of Mormon
*
*  Estimated time: 8.0hrs
*  Actual time: 2.0hrs
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <map>
using namespace std;

/******************************************************************************
 * Main handles everything in this program
 *****************************************************************************/
int main(int argc, char* argv[])
{
   // open the file from command line
   ifstream fin;
   fin.open(argv[argc - 1]);
   if (fin.fail())
   {
      cout << "open file error " << argv[argc - 1] << endl;
      return 0;
   }
   
   int total;
   string aWord;
   map < string, int > mapped;

   //Read through file tracking the number of times words show up.
   //ignore the punctuation.
   while (fin >> aWord)
   {
      for (int i = 0; i < aWord.length(); i++)
      {
         if (ispunct(aWord[i]) && aWord[i] != '-')
         {
            aWord.erase(aWord.begin() + i);
            i--;
         }
         else if (!ispunct(aWord[i]))
         {
            aWord[i] = tolower(aWord[i]);
         }
      }
      //add to the counters.
      mapped[aWord]++;
      total++;
   }
   
   cout << endl << "Number of words processed: " << total << endl;
   cout << "100 most common words found and their frequencies:\n";

   //traverse the map and find the greatest reoccurrence of words
   int j = 0;
   while (j < 100)
   {
      //iterator through removing the greatest piece after each find
      map < string, int > :: iterator it1 =  mapped.begin();
      for (map < string, int > :: iterator it2 = mapped.begin();
           it2 != mapped.end(); it2++)
      {
         if (it2->second > it1->second)
         {
            it1 = it2;
         }
      }
      // display
      cout << setw(23) << it1->first << " - " << it1->second << endl;
      mapped.erase(it1);
      j++;
   }
   fin.close();
   return 0;
}
