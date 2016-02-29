/*********************************************************/
#ifndif GRADE_H
#define GRADE_H
#include iostream

class Grade//New class! YAY!
{
  private:
   int * data;//pointer to array of intergers
   int arraySize;//declares an variable to hold array size
   
  public:
   Grade()//default constructor
   {
      data = new int[];//sets it as a new dynamically allocated array
      arraySize = 0;//sets the size to 0
   }
   Grade grade(int data)//copy constructor
   {
   }
   ~Grade grade()//destructor
   {
   }
   int getData(int data){return data};//grants access to the private
                                      //member variable data
   void setData(int data)
   {
      //  this data[0] = data[0];
      // this data[1] = data[1];
   }
   int readFile();//opens the file and reads in the data
   int addData();//should function as a linked list?
   bool checkData();//use a string compare?
   
// i hate this operator shiz...
   friend operator && ( 
};

#endif
