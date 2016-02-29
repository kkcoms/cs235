/***********************************************************************
* Program:
*    Assignment 06, Recursion
*    Brother Ercanbrack, CS235 
* Author:
*    Tyler Scott
* Summary:
*    This assignment requires you to change main and "moveObjects" so
*    "moveObjects" work recursively.  No other routines need to be
*    modified.  You may add parameters to moveObjects and modify main.
*    The classes do not need to be modified.
*
*    Note: to compile this program you must compile as follows
*           g++ -l ncurses assign6.cpp
*
*    Estimated Time: 5.0hrs
*    Actual Time: 3.0hrs
***********************************************************************/

#include <ncurses.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include <unistd.h>
#include <fstream>
using namespace std;
bool gCursesStarted = false;   // This is set to true the first time
                               // the program enters curses mode.


/*****************************************************************
 * This class is used to create a rectangle graphic object.
 * This is drawn using the ncurses library.
 ****************************************************************/
class Rectangle
{
   public:
      Rectangle();
      Rectangle(int row, int col, int height, int width);
      void move(int row, int col);
      void draw();
      void erase();
      int getRow(){ return startRow;}
      int getCol(){ return startCol;}
      void setRow(int row){startRow = row;}
      void setCol(int col){startCol = col;}
      void setHeight(int theHeight) { height = theHeight;} 
      void setWidth(int theWidth){ width = theWidth;}

   private:
      int height;     // rectangle height in screen lines
      int width;      // rectangle width in screen columns
      int startRow;   // row for upper left corner of rectangle 
      int startCol;   // column of upper left corner of rectangle
};

/**********************************************************
*  This class contains a rectangle object and the row and
*  column change increment to be used when moving the figure.
**********************************************************/
class Figure
{
   public:
      Figure(int row, int col);
      void setRowChange(int rChange){rowChange = rChange;}
      void setColChange(int cChange){colChange = cChange;}
      int getRowChange() {return rowChange;}
      int getColChange() {return colChange;}

      Rectangle box;   // the figure type
   
   private:
      int rowChange;   // row change increment
      int colChange;   // column change increment
};

/*******************************************************
* constructor -
* creates a figure object setting its upper left corner
* to row and col. It also sets the default movement
* increment for the row and column to 1 and 1 respectively
*******************************************************/
Figure::Figure(int row, int col)
  : rowChange(1), colChange(1)
{
   box.setRow(row);
   box.setCol(col);
}

// **************************************************************
// function prototypes
// ***************************************************************
void endCurses();             // ends curses mode
void startCurses();           // start curses mode
int  getInt(string prompt, int maxIntSize, string errMsg);
void pause(int value);
void moveObjects(vector < Figure > &figures, int instances, int drawCnt, int delay);


/*********************************************************************
* This program prompts the user for the number of objects they wish to
* draw.  It then draws the object, moves it to the next location and
* redraws the object. It simply illustrates the moving and redrawing
* of the object, giving the appearance of move across the screen and
* bouncing off edges of the screen.
*********************************************************************/  
int main()
{
   
   // This program must be run in putty or a terminal window in Linux.
   // It will not exit if you try executing it directly from the LINUX GUI
   if (!isatty(1))     // if not a terminal window (i.e. the GUI) exit.
   {
      exit(1);
   }


   int delay = 10;     // number between 1 and 100; 1=fastest, 100 = slowest;
   int drawCnt = 1;    // nunber of times to draw each object instance
   int figureCnt = 1;  // number of instances to draw

   int numberOfInstances = 1; //INITIALIZE INSTANCE COUNTER

   while (drawCnt > 0)
   {

      drawCnt = getInt("Number of times to draw object (0 to exit): ", 10000, 
                      "Invalid Entry - must be a between 0 - 10000!\n");
      
      if (drawCnt <= 0)
      {
         break;       // exit program 
      }

      //******************************************************************
      // ADD A NEW USER PROMPT HERE - get the number of object instances
      // use "getInt" to prompt the user for the number of instances.
      //******************************************************************
      numberOfInstances = getInt("Enter the number of instances to loop 0-15: " ,15,
                                 "Invalid Entry! - must be a number 1 -15\n");
      //prompts for the number of instances
      delay  = getInt("Enter delay between moves (1 to 100): ", 100,
                         "Invalid Entry - must be a number 1 - 100!\n");
      //prompts for the delay
      startCurses();  // Enter curses mode.

      vector < Figure > figureVec;

      //*********************************************************************  
      // MODIFY THIS CODE BELOW TO HANDLE MULTIPLE "figure" INSTANCES.
      // REMOVE THIS FOR LOOP AND MODIFY "moveObjects" TO WORK RECURSIVELY.
      // ALSO MODIFY "moveObjects" TO ACCEPT A VARIABLE NUMBER OF OBJECT
      // INSTANCES. THIS MEANS YOU WILL NEED TO ADD ADDITIONAL "figure"
      // OBJECTS TO THE FIGURE VECTOR YOU MUST PROMPT THE USER FOR THE NUMBER
      // OF INSTANCES OF THE OBJECT.
      // BASED UPON THE VALUE YOU GET FROM THE USER. YOU MUST MOVE AND DISPLAY
      // ALL OBJECT INSTANCES "drawCnt" times in "moveObjects".
      //***********************************************************************
      int row = 1;
      int col = 1;
      for (int j = 0; j < numberOfInstances; j++)//loops until reach end of instances
      {
         Figure rectangle(row, col);     // create a figure instance      
         figureVec.push_back(rectangle); // store the object instance in the vector
         row+=2;//increment the position
         col+=5; // increment the position
         if (row > LINES - 10 || row < 1)
         {
            row = 2;
         }
         
         if (col > COLS || col < 1)
         {
            col = 5;
         }
      }
      moveObjects(figureVec, numberOfInstances, drawCnt, delay);  // Move the object to next position   

      //***************************************************************************
      // END OF CODE TO BE MODIFIED
      //***************************************************************************
      
      // clear screen of any objects
      for (int i = 0; i < figureVec.size(); i++)
      {
         figureVec[i].box.erase();
      }
      refresh();    // Make sure any changes made become visible on screen.
      endCurses();  // end Curses mode
   }
}
/*******************************************************************
* MODIFY THIS FUNCTION TO WORK RECURSIVELY AND TO HANDLE MULTIPLE
* INSTANCES OF A "figure" OBJECT. ADD ANY NECESSARY PARAMETERS TO
* MAKE THIS FUNCTION WORK RECURSIVELY RATHER THAN REQUIRING A
* FOR LOOP TO MOVE THE OBJECT INSTANCES.
*
* Desc: This function moves and redraws the first object in the
*       figures vector.
*
* Inputs: figures  - vector containing one figure object.
* Outputs: figures - the "startRow" and "startCol" of the object instance
*                    in the figures vector is modified with a new location.
*******************************************************************/
void moveObjects(vector < Figure > &figures, int instances,  int drawCnt, int delay)
{
   //  if(instances == 0)
   // return;//if no instances do nothing
   // if (instanceCount == instances)
   //  return;//if the counter reaches the number of instances stop   
   int change;
   int colChange;
   int row;
   int col;

   for (int instanceCount= 0; instanceCount< figures.size(); instanceCount++)
   {         
      // get the change increment value for moving the figure
      change = figures[instanceCount]/*.front()*/.getRowChange();
      colChange = figures[instanceCount]/*.front()*/.getColChange();
      //access vector like an array and each time this is called the spot will
      // have been incremented.
      // calculate the new row and col positions;
      row = figures[instanceCount]/*.front()*/.box.getRow() + change;
      col = figures[instanceCount]/*.front()*/.box.getCol() + colChange;

      // implements change of direction when object gets to the edge of screen
      // Makes it appear to bounce off window and change direction
      if (row > LINES - 5 || row < 1)
      {
         change = -change;
         col = col + colChange;
         if (col < 1) col = 1;
      }
      
      if (col > COLS - (colChange + 5) || col < 1)
      {
         row = row + change;
         change = -change;
         colChange = -colChange;
         col = col + colChange;
      }
      figures[instanceCount]/*.front()*/.setRowChange(change);
      figures[instanceCount]/*.front()*/.setColChange(colChange);
      figures[instanceCount]/*.front()*/.box.move(row, col);
      
   }
      refresh();               // refresh the screen 
      pause(delay);            // time delay between moves
      if(drawCnt > 0)
         moveObjects(figures, instances, drawCnt--, delay);
      //recursively call the function      

}

//STOPHERE
/************************************************************
* default constructor
* Initialize rectangle object to size 1 x 3
* and places in if upper left corner of the screen
* at row 1, col 1
************************************************************/
Rectangle::Rectangle()
{
   height = 1;   // rectangle height in screen rows
   width = 3;    // rectangle width in screen columns
   startRow = 1;
   startCol = 1;
}

/********************************************************************
* constructor
* inputs: row & col - upper left corner screen location of rectangle
*         height & width -  rectangle size (in rows and columns)
******************************************************************/
Rectangle::Rectangle(int row, int col, int theHeight, int theWidth)
{
   startRow = row;
   startCol = col;
   height = theHeight;
   width = theWidth;
}

/***************************************************************************
* draw()
* This routine draws the rectangle
* using special characters such as ACS_ULCORNER and ACS_VLINE.
* The frame extends from startRow to endRow vertically and from
* startCol to endCol horizontally.  (Rows and columns are numbered
* starting from 0.)  Note that the interior of the frame extends
* from startRow+1 to endRow-1 vertically and from startCol+1 to
* endCol-1 horizontally.
*************************************************************************/
void Rectangle::draw()
{
   int endRow = startRow + height;
   int endCol = startCol + width;
   mvaddch(startRow,startCol,ACS_ULCORNER);
   for (int i = startCol + 1; i < endCol; i++)
   {
      addch(ACS_HLINE);
   }
   addch(ACS_URCORNER);
   for (int i = startRow + 1; i < endRow; i++)
   {
      mvaddch(i,startCol,ACS_VLINE);
      mvaddch(i,startCol + width,ACS_VLINE);
   }
   mvaddch(endRow,startCol,ACS_LLCORNER);
   for (int i = startCol + 1; i < endCol; i++)
   {
      addch(ACS_HLINE);
   }
   addch(ACS_LRCORNER);
}

/********************************************************
* This routine erases the rectangle by writing spaces
* over the rectangles line characters
*******************************************************/
void Rectangle::erase()
{
   int endRow = startRow + height;
   int endCol = startCol + width;

   mvaddch(startRow,startCol,' ');
   for (int i = startCol + 1; i < endCol; i++)
   {
      addch(' ');
   }
   addch(' ');
   for (int i = startRow + 1; i < endRow; i++)
   {
      mvaddch(i, startCol,' ');
      mvaddch(i, endCol,' ');
   }
   mvaddch(endRow, startCol,' ');
   for (int i = startCol + 1; i < endCol; i++)
   {
      addch(' ');
   }
   addch(' ');
}

/*******************************************************************
* Desc:  This function moves the rectangle from its current
* location to the newly specified location.
* It first call erase(), then sets the new coordinates
* and draws the new rectangle.
*
* Inputs:  row, col -  rectangle upper left corner screen row and col 
*******************************************************************/
void Rectangle::move(int row, int col)
{
   erase();      // erase current object
   startRow = row;
   startCol = col;
   draw();      // draw at new location
}

/***********************************************************************
*  This function is used to create a time delay or pause.
**********************************************************************/
void pause(int value)
{
   unsigned long ulength = value * 1000;
   usleep(ulength);   //sleep time in microseconds; 
}

/************************************************************************
*  int getInt(string prompt, string errMsg)
*
*  Desc: Error safe - read integer routine
*        On error, this function will re-prompt for the integer
*        until there is no input error.
*
*  Inputs:  prompt - string used to prompt for the integer
*           maxSize - maximum integer size allowed.
*           errMsg - error message you wish displayed if you get an error.
*  Outputs: none
*  return:  integer <= maxSize - read from the console
**************************************************************************/
int getInt(string prompt, int maxSize, string errMsg)
{
   int promptCnt = 0;
   int integer;
   cout << prompt;
   cin >> integer;
   while (cin.fail () || integer < 0 || integer > maxSize)
   {
      promptCnt++;        // count how many times the errors
      cout << errMsg;
      cin.clear ();
      cin.ignore (128, '\n');
      if (promptCnt < 5) // don't prompt more than 5 times
      {
         cout << prompt;
         cin >> integer;
      }
      else
      {
         cout << "To many invalid user attempts! Returning a value of zero!\n";
         return 0;
      }
   }
   return integer;
}

/********************************************************************
* This will exit curses mode and return the console to the usual
* line-oriented input/output mode.  If it is called when curses
* mode is not in effect, it will have no effect.
*********************************************************************/
void endCurses()
{
   if (gCursesStarted && !isendwin())
   {
      endwin();
   }
}

/***********************************************************************
* This will put the console into curses mode.  If curses mode is being
* entered for the first time, the screen will be cleared.  If it is
* being re-entered after a call to endCurses(), then the previous
* screen contents will be restored.
***********************************************************************/
void startCurses()
{
   if (gCursesStarted)
   {
      refresh();
   }
   else
   {
      initscr();
      cbreak();
      noecho();
      intrflush(stdscr, false);
      keypad(stdscr, true);
      atexit(endCurses);  // Make sure endCurses() is called when program ends.
      gCursesStarted = true;
   }
}
