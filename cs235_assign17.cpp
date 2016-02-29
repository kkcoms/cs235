/******************************************************************************
* Program:
*    Assignment 17, Heap Sort
*    Brother Ercanbrack, CS 235
* Author:
*    Tyler Scott
* Summary:
*    This program implements a heap sort
*
*  Estimated time: 8.0hrs
*  Actual time: 4.0hrs
******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/******************************************************************************
 * Swaps two integer values assigned positions
 *****************************************************************************/
void swap(int &a, int &b)
{
   int temp = a;
   a = b;
   b = temp;
}

/******************************************************************************
 * Shifts right low to high
 *****************************************************************************/
void shiftRight(vector < int > &nums, int low, int high)
{
   int root = low;
   while ((root * 2) + 1 <= high)
   {
      int leftChild = (root * 2) + 1;
      int rightChild = leftChild + 1;
      int swapIdx = root;

      //Check if root is less than left child*/
      if (nums[swapIdx] < nums[leftChild])
      {
         swapIdx = leftChild;
      }

      //If right child exists check if it is less than current root
      if ((rightChild <= high) && (nums[swapIdx] < nums[rightChild]))
      {
         swapIdx = rightChild;
      }

      //Make the biggest element of root, left and right child the root
      if (swapIdx != root)
      {
         swap(nums[root], nums[swapIdx]); 

         //Keep shifting right and ensure that swapIdx satisfies
         //heap property aka left and right child of it is smaller than
         //itself
         root = swapIdx;
      }
      else
      {
         break;
      }
   }
   return;
}

/******************************************************************************
 *  Start with middle element. Middle element is chosen in such a way that
 *  the last element of array is either its left child or right child
 *****************************************************************************/
void heapify(vector < int > &nums, int low, int high)
{
   int midIdx = (high - low - 1) / 2;
   while (midIdx >= 0)
   {
      shiftRight(nums, midIdx, high);
      --midIdx;
   }
   return;
}

/******************************************************************************
 * Sorts the values using the shift right function
 *****************************************************************************/
void heapSort(vector < int > &nums, int size)
{
   if (size > 0)
   {
      //This will put max element in the index 0
      heapify(nums, 0, size - 1);
      int high = size - 1;
      while (high > 0)
      {
         //Swap max element with high index in the array
         swap(nums[high], nums[0]);
         --high;
         
         //Ensure heap property on remaining elements
         shiftRight(nums, 0, high);
      }
      return;
   }
   else
      return;
}

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
   vector < int > nums; 
   int data;
   int size = 0;

   while (fin >> data)
   {
      nums.push_back(data);
      size++;
   }
   heapSort(nums, size);
   for (int i = 0; i < nums.size(); i++)
   {

      cout << nums[i] << " ";
   }
   cout << endl;
   fin.close();
   return 0;
}
