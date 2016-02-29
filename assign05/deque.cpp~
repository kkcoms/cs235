/***********************************************************************
 * Program:
 *    Assignment 05, Stocks Deque
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Tyler Scott
 * Summary:
 *   This program reads in from a file and uses the stock information
 *   via a deque abstract data type
 * Estimated time: 5hrs
 * Actual time: 7hrs
 ***********************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <deque>
using namespace std;

/***************************************************
 *Stock Structure to be object oriented
 ***************************************************/
struct Stockade
{
   int numberOfShares; //variable
   float pricePerShare; //variable
};

/*****************************************************
 *MAIN CHEESE
 ****************************************************/
int main(int argc, char** argv)
{
/*****************READ FILE***************************/
   string filename = "";
   if( argc == 2 )
   {
      filename = argv[1];
   }
   else
   {
      getline(cin, filename);
   }
   //input the file from the command line

   ifstream fin;
   fin.open(filename.c_str());//open the file
   if(fin.fail())
   {
      cout << "Error reading File...";
      return 0;//if the file cant open display error
   }
   string tranType; // variable for type of transaction
   int totalStock; // variable to keep track of the total remaining stocks
   float expense; // variable to keep track of the expenses made
   float profit; // variable to keep track of the profit made
   float loss; // variable to keep track of profit loss
   float gain; // variable to keep track of profit gain
   Stockade buy;// call da struct for buying
   Stockade sell; // call da struct for selling
   deque<Stockade> d; // make a new deque to pump up the jam
   
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2); // to make it look pretty
   
/*********************Manipulate DATA **********************/   
   for(int i =0;!fin.eof();i++)
//Loop through until you reach the end of the file
   {
      fin >> tranType;// >> numStocks >> price;// read in the data

      if(tranType == "BUY")
      {
         fin >> buy.numberOfShares;// = numStocks;
         fin >> buy.pricePerShare;// = price; 
         d.push_back(buy);
//push the stock object onto back of deck (behind previous)
         cout << "Bought " << buy.numberOfShares << " shares at $"
              << buy.pricePerShare << endl;// " per share.\n";
         // expense = buy.numberOfShares * buy.pricePerShare; //expense tracking
         //  cout << "expense: $" << expense << endl;
         totalStock += buy.numberOfShares; // qty of shares tracking
      }
      
      else if(tranType == "SELL")
      {
         fin >> sell.numberOfShares;// = numStocks;
         fin >> sell.pricePerShare;// = price;
//         cout << "Sold " << sell.numberOfShares << " stocks @ $"
         //            << sell.pricePerShare << " per share.\n";
      
         buy = d.front();//make sure your pointing to the first     
         int pop1 =  buy.numberOfShares - sell.numberOfShares;
         //subtract shares sold 
         if(pop1 < 0)// if you run out of shares pop another set off
         {
            profit = buy.numberOfShares*buy.pricePerShare;// calculate initial profit                  
            d.pop_front(); // pop off the first object (remove it)
            buy = d.front(); // point to the next object behind it
            buy.numberOfShares += pop1; // 2nd objects shares are added to the
                                        //current your working with (negative number)
            profit -= pop1*buy.pricePerShare; // calculate your new profit
            profit = ((sell.numberOfShares * sell.pricePerShare) - profit);
                 // subtract this profit from the sale profit
            d.push_front(buy);// push the newly changed object onto the deque, in the front
            d.pop_back();
         }
         else
         {
            buy.numberOfShares -= sell.numberOfShares;// subtract the sold shares from the old ones bought
            profit = ((sell.numberOfShares * sell.pricePerShare) - (sell.numberOfShares * buy.pricePerShare));
            //calculate the new profit (gain - loss)
            d.pop_front(); // pop off the first object (remove it)        
            d.push_front(buy);// push the newly changed object onto the deque, in the front
         }
         totalStock -= (sell.numberOfShares); // qty of shares tracking      
         cout << "Sold " << sell.numberOfShares << " shares at $" << sell.pricePerShare << " for a profit of $";
         
         if (profit > 0)
         {
            cout << profit << endl; // display your profit
            gain += profit;// Accumulate the gain
         }
         else
         {
            cout << "(" << profit*-1 << ")" << endl; // display your profit negative
            loss += profit; // Accumulate the loss
         }

      }
      //  expense += expense;  
   }
   fin.close();// close da file
   cout << endl;
//   cout << "Total Shares = " << totalStock << endl;
   cout << "Total Profit: $" << gain + loss << endl; //display the total profit
   cout << "\nUnsold Shares\n";
   Stockade display;//new stock structure
   int size =  d.size();//initialize size or there are issues because
                        // d.size() is constantly changing
   for (int i = 0; i < size; i++)
   {
      display = d.front(); // point to the front object        
      if(display.numberOfShares <= 0)//if there are no shares
         break;//do nothing ie dont display
      else   
      {
         cout << "   " << display.numberOfShares << " shares bought for $"
              << display.pricePerShare << endl; // " per share.\n"; // display object
         d.pop_front(); // pop it off and move on
      }
   }
   return 0;
}
