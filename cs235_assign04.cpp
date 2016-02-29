/***********************************************************************
 * Program:
 *    Assignment 04, Airport Simulation Queue
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Tyler Scott
 * Summary: 
 *   This program simulates an airport queue
 * Estimated time: 5hrs
 * Actual time: 7hrs
 ***********************************************************************/
#include <iostream>
#include <iomanip>
#include <math.h>
#include <cstdlib>
#include <time.h>
using namespace std;

//CLASSES...
/*************************************************
 *queue class
 *************************************************/
template <class T>
class Queue
{
   private:
      int front;                  // --- index of front of queue
      int back;                   // --- index of back of queue
      int maxSize;                // --- max storage capacity of array
      int numItems;               // --- number of items currently in queue
      T *queueItems;            // --- array containing queue items
  
   public:
      Queue(int size = 100);           // --- constructor
      Queue(const Queue<T> &aQueue); //  copy constructor
      ~Queue(void);               // --- destructor
      void insert(T item);      // --- insert item into back of queue
      T remove(void);           // --- remove item from front of queue
      bool empty(void);            // --- returns 1 if queue is empty, 0 otherwise
      bool full(void);             // --- returns 1 if queue is full, 0 otherwise
      Queue<T>& operator = (const Queue<T> &rtSide); // overloaded assignment operator
      int getNumItems(){return numItems;};// enables acess to the private variable numItems
};

/*****************************************************
 *Random number generator
 *****************************************************/
class Random
{
public:
   Random();

   /* --- Get next Poisson random --- */
   int poissonRandom(double expected);
};

/***************************************************
 *Class for airplane object
 ***************************************************/
class Airplane 
{
private:
   double waitT; // initialize waitime
public:
   Airplane();//constructor
   double getWaitT();//enable access to private variable
   void setWaitT(double curtime);
};

//****************************METHODS**********************************

/**********************************************************************
 * default constructor
 **********************************************************************/
template <class T>
Queue<T>::Queue(int size)
{
   maxSize = size > 0 ? size : 100;    // if s  is negative, set queue size to 100
   numItems = 0;
   back = front = maxSize - 1;
   queueItems = new T[maxSize];
}

/**********************************************************************
 * destructor
 **********************************************************************/
template <class T>
Queue<T>::~Queue(void)
{
   delete [] queueItems;
}

/***********************************************************************
 * Queue Copy Constructor
 ***********************************************************************/
template <class T>
Queue<T>::Queue(const Queue<T> &aQueue)
{
   maxSize = aQueue.maxSize;
   numItems = aQueue.numItems;
   front = aQueue.front;
   back = aQueue.back;
   queueItems = new T[maxSize];
   for (int i = 0; i < maxSize; i++)
   {
      queueItems[i] = aQueue.queueItems[i];
   }
}

/***********************************************************************
 * Overloaded assignment operator.
 ***********************************************************************/
template <class T>
Queue<T>& Queue<T>::operator =(const Queue<T> &rtSide)
{
   if (this != &rtSide)
   {

      if( maxSize != rtSide.maxSize)
      {
         delete [] queueItems;
         queueItems = new T[rtSide.maxSize];
      }

      for (int i = 0; i < rtSide.maxSize; i++)
      {
         queueItems[i] = rtSide.queueItems[i];
      }
      maxSize = rtSide.maxSize;   //max size of queue
      numItems = rtSide.numItems; //number of items in queue
      back = rtSide.back;
      front = rtSide.front;
   }
   return *this;
}

/**********************************************************************
 * returns true if queue is empty
 **********************************************************************/
template <class T>
bool Queue<T>::empty(void)
{
   return (numItems == 0);
}

/**********************************************************************
 * returns true if queue is full
 **********************************************************************/
template <class T>
bool Queue<T>::full(void)
{
   return (numItems == maxSize);
}

/**********************************************************************
 * inserts item into back of queue, then increments number of items
 * in queue
 **********************************************************************/
template <class T>
void Queue<T>::insert(T item)
{
   // --- check for overflow
   if (full())
   {
      cout << "Queue overflow" << endl;
      exit(1);
   }
   queueItems[back] = item;
   back = (back + 1) % maxSize;
   numItems++;
}

/**********************************************************************
 * removes item from front of queue, then decrements number of items
 * in queue
 **********************************************************************/
template <class T>
T Queue<T>::remove(void)
{
   T temp;
   if (empty())
   {
      cout << "queue underflow" << endl;
      exit(1);
   }
   temp = queueItems[front];
   front = (front + 1) % maxSize;
   numItems--;
   return (temp);
}

//constructor for random class
Random::Random()
{
   // srand((int)time(NULL));   // variable seed for real simulation
   srand(2500);                 // fixed seed for debug and grading
}
//i dont fully know how this thing works
int Random::poissonRandom(double expected)
{
   int n=0;
   double limit;
   double x;

   limit = exp(-expected);
   x = rand() / ((double)RAND_MAX + 1);
   while (x > limit)
   {
      n++;
      x *= rand() / ((double)RAND_MAX + 1);
   }
   return n;
}
/***********************************************
 *constructor re
 **********************************************/
Airplane :: Airplane()
{
   waitT = 0;
}
/********************************************/
double Airplane :: getWaitT()
{
   return waitT;
}
/***********************************************/
void Airplane :: setWaitT(double curtime)
{
  this->waitT = curtime;
}


/*****************************************************************
 * Main
 ****************************************************************/
int main()
{
   //makes it look pretty
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   //Intialize neccessary variables.
//for the random!
   Random rand1;
   Random rand2;
   int random1 = 0;
   int random2 = 0;
//stuff to input
   double simTime = 0;
   double pArrivals = 0;
   double pDeparts = 0;
//new queue objects
   Queue<int> arrival(5);
   Queue<int> depart(5);
//counters to keep tabs on
   int planes = 0;
   int aDenied = 0;
   int tDenied = 0;
   int lands = 0;
   int takeoffs = 0;

   //names for calculations
   float timeIdle =0;
   float totalArrival = 0;
   float totalDepart = 0;
   float avgTimeIdle = 0;
   float avgTimeA = 0;
   float avgTimeD = 0;

//prompts for data 
   cout << "Units of time the simulation will run: ";
   cin >> simTime;
   cout << "Expected number of arrivals per time unit: ";
   cin >> pArrivals;
   cout << "Expected number of take offs per time unit: ";
   cin >> pDeparts;

     //loopdy doo, 
   for (int curtime = 1; curtime <= simTime; curtime++)
   {
      random1 = rand1.poissonRandom(pArrivals);
      random2 = rand2.poissonRandom(pDeparts);
      
      for (int j = 0; j < random1; j++)
      {
         Airplane plane1;
         plane1.setWaitT(curtime);
         planes++;         
         if(!arrival.full())//while the queue is not full
         {
            arrival.insert(plane1.getWaitT());
            //insert the planes into the arrival queue
         }
         else
         {
            aDenied++;
            //if its full deny arrival
         }
      }
      for (int l = 0; l < random2; l++ )
      {
         Airplane plane2;
         plane2.setWaitT(curtime);
         planes++;
         if(!depart.full())//while the queue is not full
         {
            depart.insert(plane2.getWaitT());
            //insert the planes into the depart queue
         }
         else
         {
            tDenied++;
            //if its full deny departure
         }
      }
      if (!arrival.empty())//while the arrival queue isnt empty
      {
         totalArrival = totalArrival + (curtime - arrival.remove());
         //offload from the queue
         lands++;// increment the number of lands counter
      }
      else if (!depart.empty())
      {
         totalDepart = totalDepart + (curtime - depart.remove());
         //offload the queue
         takeoffs++;//increment the number of takeoff counter
      }
      else
         timeIdle++;//if nothings going on increment the time counter
   }
   
   //calculate stuff
   avgTimeIdle = (timeIdle/simTime) * 100;//calculates percentage
   avgTimeA = (totalArrival/lands);
   avgTimeD = (totalDepart/takeoffs);

   //display info
   cout << endl;   
   cout << "Total number of planes processed: " << planes << endl
        << "Number of planes landed: " << lands << endl
        << "Number of planes taken off: " << takeoffs << endl
        << "Number left ready to land: "  << arrival.getNumItems() << endl
        << "Number left ready to take off: " << depart.getNumItems() << endl
        << "Number of planes refused use: " << tDenied + aDenied << endl
        << "Percentage of time runway idle: "<< avgTimeIdle << "%" << endl
        << "Average wait time to land: " << avgTimeA << endl
        << "Average wait time to take off: " << avgTimeD << endl;
   return 0;
}
         
       
