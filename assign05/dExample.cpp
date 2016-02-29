#include <iostream>
#include <deque>
using namespace std;
int main()
{
   deque<int> d;
   
// Output number of values stored in d
   cout << "Size: " << d.size() << endl;

// Add first 6 integers alternatingly to front and back
   for (int i = 1; i <= 6; i++)
   {
      cout << "Adding " << i << " to front..." << endl;
      d.push_front(i++);
      cout << "Adding " << i << " to back..." << endl;
      d.push_back(i);
   }

// Display contents of d from front to back
   cout << "Contents of deque from front to back: ";
   for (int i = 0; i < d.size(); i++)
      cout << d[i] << "  ";
   cout << endl;

// Change back value to 999, remove front value;
   cout << "Changing back value to 999..." << endl;
   d.back() = 999;
   cout << "Removing front value..." << endl;
//  d.pop_front();
   d[2] = 0;
// Display contents of d again, but use an iterator
   cout << "Contents of deque from front to back (iterator): ";
   for (deque<int>::iterator it = d.begin(); it != d.end(); it++)
      cout << *it << "  ";
   cout << endl;

// Dump contents of d from back to front
   cout << "Contents of deque from back to front: ";
   while (!d.empty())
   {
      cout << d.back() << "  ";
      d.pop_back();
   }
   cout << endl;
}
