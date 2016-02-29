/***********************************************************************
* Program:
*    Assignment 08, Polynomials
*    Brother Ercanbrack, CS 235
* Author:
*    Tyler Scott
* Summary: 
*    This program reads two polynomials from a file, displays them,
*    adds them together, evaluates the result for a given value of x and
*    displays the result.
* Estimated time: 8.0hrs
* Actual time: 11.0hrs
***********************************************************************/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/******************************************************************************
*  Author: Brother Cameron, 10/9/2001
*  Purpose: Defines classes for a Term and a Polynomial
******************************************************************************/
class Term
{
   private:
      float coeff;
      int expon;
 
   public:
      Term();                  // --- Creates empty Term
      Term(float c, int e);    // --- Creates Term object with coeff. c 
                               //and expon. e
      float getCoeff(void);    // --- returns coeff of term
      int getExpon(void);      // --- returns expon of term
      void setCoeff(float c);  // --- sets term's coeff. to c
      void setExpon(int c);    // --- sets term's expon to c
};

/***********************************************************************
* Class containing an array of Terms and the functions to operate on them
***********************************************************************/
class Poly
{
   private:
      int numTerms;            // number of terms in polynomial
      int maxItems;            // array capacity
      Term *terms;             // dynamically allocated array of terms

   public:
      Poly();                  // creates empty polynomial
      Poly(const Poly &poly);  // copy constructor
      ~Poly();                 // destructor free dynamically allocate ptrs.
      void insertTerm(Term t); // inserts Term t into polynomial
      int getNumTerms(void);   // returns number of terms in array
      Term getTerm(int index); // returns term at index
      Poly& operator = (const Poly& rightSide);//overloaded assignment operator
      float operator () (float x);
};

ostream& operator << (ostream& outFile, Poly& op1);
istream& operator >> (istream& inFile, Poly& op1);
Poly operator + (Poly& op1, Poly& op2);

/***********************************************************************
* Main reads the file, outputs the polynomials, adds them together and
* displays the results.  Don't modify this function!!!!!
***********************************************************************/
int main(int argc, char* argv[])
{
   ifstream inFile;
   inFile.open(argv[argc - 1]);
   if (inFile.fail())
   {
      cout << "open file error " << argv[argc - 1] << endl;
      exit(1);
   }
   
   Poly f;
   Poly g;
   Poly p;

   int value (0); // value of x for evaluation
   inFile >> f;
   inFile >> g;

   cout << "F(x) =  " << f << endl;
   cout << "G(x) =  " << g << endl;

   // make copies of the polynomials
   Poly temp1(f);
   Poly temp2(g);

   // add polynomials f and g
   p = f + g;
   cout << "\nP(x) = (F + G)(x) = " << p << endl;

   // read in a value for X
   inFile >> value;

   // evaluate the polynomial
   cout << "P(" << value << ") = " << p(value) << endl << endl;

   // swap temp1 and temp2 - shouldn't change f & g
   Poly temp3(temp2);
   temp2 = temp1;
   temp1 = temp3;

   // Insert a new term 8x^6
   temp1.insertTerm(Term(8,6));

   cout << "temp1(x) is same as 8x^6 + G(x) or " << temp1 << endl;
   cout << "temp2(x) is same as F(x) or " << temp2 << endl;
   cout << "temp3(x) is same as G(x) or " << temp3 << endl << endl;

   cout << "Original functions were:" << endl;
   cout << "F(x) =  " << f << endl;
   cout << "G(x) =  " << g << endl;

   inFile.close();
   return 0;
}

/*****************************************************************************
*  Function: Term
*
*  Parameters - none
*  Return Value - none
*
*  Purpose - Constructor function for Term class.  Creates empty Term.
****************************************************************************/
Term::Term(void)
{
   coeff = 0.0;
   expon = -1;  // --- guarantees insert will occur
}

/*****************************************************************************
*  Function: Term
*
*  Parameters - a float that is the coefficient and a int that is the expon.
*  Return Value - None
*
*  Purpose: Creates a Term object set to coefficient and expon.
****************************************************************************/
Term::Term(float c, int e)
{
   coeff = c;
   expon = e;
}

/******************************************************************************
*  Function: getCoeff
*
*  Parameters: None
*  Return Value - an integer representing coeff.
*
*  Purpose: Returns the coefficient data member of Term class
****************************************************************************/
float Term::getCoeff(void)
{
   return (coeff);
}

/***************************************************************************
*  Function: getExpon
*  Purpose: Returns the expon data member of Term class
*
*  Parameters - none
*  Return value - integer, representing expon.
***************************************************************************/
int Term::getExpon(void)
{
   return (expon);
}

/***************************************************************************
*  Function: setCoeff
*  Purpose: sets c to data member coeff in Term class
*
*  Parameters - float representing coeff
*  Return value - none
**************************************************************************/
void Term::setCoeff(float c)
{
   coeff = c;
}

/***************************************************************************
*  Function: setExpon
*  Purpose: sets e to data member expon in Term class
*
*  Parameters - int representing expon
*  Return value - none
**************************************************************************/
void Term::setExpon(int e)
{
   expon = e;
}

/***************************************************************************
*  Function: Poly
*  Purpose:  Poly class constructor to create an empty Poly object of 50 
*            term.
*
*  Parameters - none
*  Return value - none
**************************************************************************/
Poly::Poly()
{
   numTerms = 0;
   terms = new Term [50];
   maxItems = 50;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////HERE!!!!!///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/********************************************
 * Destruction!!! look out for Godzilla!
 *********************************************/
Poly::~Poly()
{
    delete [] terms;
    terms = NULL;
}

/*******************************************
 * copy constructor
 ********************************************/
Poly::Poly(const Poly &poly)
{
   numTerms = poly.numTerms;//copy each piece
   maxItems = poly.maxItems;
   terms = new Term [maxItems];
   for (int i = 0; i < maxItems; i++)
   {
      terms[i] = poly.terms[i];
   }
}

/*******************************************
 * overloaded Assignment operator
 ********************************************/
Poly& Poly::operator = (const Poly &rightSide)
{//assign rightside to the left
   if (this != &rightSide)
   {
      if (maxItems != rightSide.maxItems)
      {
         if (terms != NULL)
            delete [] terms;
       
         terms = new Term[rightSide.maxItems];
      }
      for (int i = 0; i < rightSide.maxItems; i++)
      {
         terms[i] = rightSide.terms[i];
      }
      numTerms = rightSide.numTerms;
      maxItems = rightSide.maxItems;
   }
   return *this;   
}

/***********************************************************************
* Inserts a term into a polynomial in the proper location.  If a term
* is inserted with a duplicate exponent, the terms are combined.  If any
* coefficient goes to zero that term is removed from the polynomial.
***********************************************************************/
void Poly::insertTerm(Term t)
{ 
//   float tempe;//temporary exponent holder
   float tempc;//temporary coefficent holder
   if(numTerms == 0)//check if the number of terms is zero
   {
      terms[0].setCoeff(t.getCoeff());//if it is set the first positions coefficent to t's
      terms[0].setExpon(t.getExpon());//if it is set the first positions exponent to t's
      numTerms++;//increment the number of terms counter now that one is in there
      return;
   }
 
   for(int i = 0; i <= numTerms; i++)
   {//loop through array positions as long as its less than or equal the numTerms
      if(terms[i].getExpon() == -1)//if the exponent in the current array position is -1
      {
         terms[i].setExpon(t.getExpon());//set the exponent with t's to current array position
         terms[i].setCoeff(t.getCoeff());//set the coefficent with t's to current array position
         numTerms++; //increment the number of terms counter now that another one is in there
         return;
      }

      if(terms[i].getExpon() < t.getExpon())//if the arrays exponent is less than t's
      {
         for(int j = numTerms; j > i; j--)// loop through and insert it the position before that.
            terms[j] = terms[j-1];//the current array position is moved back one 
       
         terms[i].setExpon(t.getExpon()); // set the exponent
         terms[i].setCoeff(t.getCoeff()); // set the coefficent
         numTerms++;//increment the number of terms counter now that one is in there    
         return;            
      }          
      
      if(terms[i].getExpon() == t.getExpon())//if the exponents are the same
      {
         tempc = terms[i].getCoeff() + t.getCoeff();// t object coefficents add together`
         t.setCoeff(tempc);// set the coefficent of t to the added number       
         if(tempc != 0)// if the new t coefficent dont add up to zero
         {
            terms[i].setCoeff(t.getCoeff());//the t object gets assigned to that array position
            terms[i].setExpon(t.getExpon());//the t object gets assigned to that array position
            
         }
         if(tempc == 0)//if the t coefficent adds up to zero
         {
            for(int k = i; k < numTerms; k++)//loop from current array position to the end
               terms[k] = terms[k+1];// copy the term in the next position to the current one
            
            numTerms--;//decrement the size
            return;
         }
         return;
      }
   }  
}

/***********************************************************************
* Accessor function that returns the number of Terms in the array
***********************************************************************/
int Poly::getNumTerms()
{
   return (numTerms);
}

/***********************************************************************
* Accessor function that returns the Term at a given index
***********************************************************************/
Term Poly::getTerm(int index)
{
   return (terms[index]);
}

/***********************************************************************
* overloaded () operator that evaluates the polynomial for the value
* within the parentheses
***********************************************************************/
float Poly::operator () (float x)
{   
   float totals;//variable holds the running total
   for(int i = 0; i < numTerms; i++)//loop through the terms in the polynomial
   {
      totals += pow(x, terms[i].getExpon()) * terms[i].getCoeff();
      //totals is equal to itself plus the passed in x value raised to the exponent
      // muliplied by its leading coefficent
   }
   return totals;//return the total evaluated
}

/***********************************************************************
* overloaded + operator that combines two polynomials and returns the
* result as a polynomial
***********************************************************************/
Poly operator + (Poly& op1, Poly& op2)
{
   Poly op3;//temporary polynomial
   int tempNt = op3.getNumTerms();//temperary number of terms
   if(op1.getNumTerms()!= op2.getNumTerms() && op1.getNumTerms() > op2.getNumTerms())
      tempNt = op1.getNumTerms();
   //if the op1 numTerms is greater than the op2 numterms and they are not equal
   //set the temporary number of terms to op1 kenobi's
   else if(op1.getNumTerms()!= op2.getNumTerms() && op1.getNumTerms() < op2.getNumTerms())
      tempNt = op2.getNumTerms();
      //if the op2 numTerms is greater than the op1 numterms and they are not equal
   //set the temporary number of terms to op2d2 
   else//otherwise
      tempNt = op1.getNumTerms();//set the temporary number of terms to op1 kenobi's
   for (int i =0; i < tempNt; i++)//loop through till the end of the terms
   {
      Term tempTa = op1.getTerm(i);//get a term from op1 kenobi
      Term tempTb = op2.getTerm(i);//get a term from op2d2 
      op3.insertTerm(tempTa);//insert the terms from each onto the temp poly
      op3.insertTerm(tempTb);
   }
   return op3;//return the polynomial
}
  
/***********************************************************************
* overloaded << operator that outputs the polynomial in the proper format
***********************************************************************/
ostream& operator << (ostream& outFile, Poly& op1)
{
   for (int i =0; i < op1.getNumTerms(); i++)//loop through till you reach the end of the terms
   {
      Term tempTa = op1.getTerm(i);//get the term and store it in tempTa variable
      if(tempTa.getCoeff() == 1) // if the coefficent is 1
      {
         if(tempTa.getExpon() == 0)// if the exponent is 0
         {
            if(i == 0)// if the postition is the first one
               outFile << tempTa.getCoeff();//output the coefficent only ie 1(x^0)=1
            else//otherwise ie its not the first in the listed polynomial
               outFile << " + " << tempTa.getCoeff();//output a + sign first
         }
         else if(tempTa.getExpon() == 1)//if the exponent is 1 
            outFile << " + x"; //output an x only
         else//if the exponent is anything else
         {
            if(i>0)//check if the position is > 0.
               outFile << " + x^" << tempTa.getExpon();//then output + xraised to the exponent
                                                       // coefficent is already 1
            else//if it is less than 0
               outFile << "x^" << tempTa.getExpon(); // ignore the + sign
         }
      }
      
      else if(tempTa.getCoeff() == -1)// if the coefficent is -1
      {
         if(tempTa.getExpon() == 0)//if the exponent is 0
         {           
            if(i == 0)// if the postition is the first one
               outFile << tempTa.getCoeff();//outpit the coefficent only
            else//otherwise
               outFile << " - " << tempTa.getCoeff()*-1; //out put a - sign then the coefficent
         }
         else if(tempTa.getExpon() == 1)//if the exponent is 1
            outFile << " - x";//output just the x
         else//if the exponent is anything else
         {
            if(i>0)//check if the position is greater than 0
               outFile << " - x^" << tempTa.getExpon();//if it is output a - x raised to exponet
            else//if its not
               outFile << "-x^" << tempTa.getExpon(); //output it as a negative x
         }
      }
      
      //im getting tired of comments...
      else if(tempTa.getCoeff() > 0)//if the coefficent is positive
      {//same procedure
         if(tempTa.getExpon() == 0)  // exponent is zero
            outFile << " + " << tempTa.getCoeff(); //output the coefficent only
         else if(tempTa.getExpon() == 1)// if the exponent is 1
            outFile << " + " << tempTa.getCoeff() << "x"; //out put the coefficent with an x not raised
         else//any other exponent
         {
            if(i>0)//check that the position isnt the first
               outFile << " + "<< tempTa.getCoeff(); // if its not then output a + sign first
            else//if it is
               outFile << tempTa.getCoeff();//just output the coefficent

            outFile << "x^" << tempTa.getExpon(); //then output the exponent
         }
      }
      
      else if(tempTa.getCoeff() < 0)//if the coefficent is negative
      {//same procedure only with - signs
         if(tempTa.getExpon() == 0)
            outFile << " - " << tempTa.getCoeff()*-1;
         else if(tempTa.getExpon() == 1)
            outFile << " - " << tempTa.getCoeff()*-1 << "x";
         else
         {
            if(i>0)
               outFile << " - " <<  tempTa.getCoeff()*-1;
            else
               outFile << tempTa.getCoeff();
            
            outFile << "x^" << tempTa.getExpon();
         }         
      }
   }
   return outFile; // return the output 
}

/***********************************************************************
* overloaded >> operator that reads an entire polynomial into an array
* of Terms in the proper order.
***********************************************************************/
istream& operator >> (istream& inFile, Poly& op1)
{
   int size = 0;//initialize a variable to hold the input polynomial size
   float inCo;//initialize a variable to hold the input coefficents
   int inEx;//initialize a variable to hold the input exponents
   inFile >> size;//read in the size or number of terms
   for (int i = 0; i < size; i++)//loop till you reach the end of the terms
   {
      inFile >> inCo;//read in the coefficent
      inFile >> inEx;//read in exponent
      // cout << " read in: " << inCo;//test that its working
      // cout << " " << inEx << endl;//test that its working
      Term tempT;//initialize a temporary term to hold the combined pieces of the term
   
      tempT.setCoeff(inCo);//set the terms coefficent with the read in one
      tempT.setExpon(inEx);//set the terms exponent with the read in one
      op1.insertTerm(tempT);//insert the terms into the polynomial
   }
   return inFile; 
}
