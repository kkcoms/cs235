/*****************************************/
#include "stacker.cpp"
//#include "tStacker.cpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
//#include <algorithm>
using namespace std;

string pfix(string exp);
void displayMachineCode(string exp);

int main(int argc, char** argv)
{
   string filename = "";
   if( argc == 2 )
   {
      filename = argv[1];
   }
   else
   {
      getline(cin, filename);
   }
   
   ifstream fin;
   fin.open(filename.c_str());
   if(fin.fail())
   {
      cout << "Error reading File...";
      return 0;
   }
   string infixExp;
   for (; !fin.eof(); )
   {
         getline(fin, infixExp);
//         if (infixExp == "#")
         //          break;
         if(!fin.fail())
         {
         cout << "Infix Expression: " << infixExp << endl;
         cout << "Postfix expression: " << pfix(infixExp) << endl;
         }
   displayMachineCode(pfix(infixExp));
   }
   fin.close();
   return 0;   
}
string pfix(string exp)
{
   char token;
   char topToken;
   Stack opStack;
   string pfixExp;
   const string BLANK = "";
   for (int i = 0; i < exp.length(); i++)
   {
      token = exp[i];
      switch(token)
      {
         case ' ':
            break;

         case '(':
            opStack.push(token);
            break;

         case ')':
            for (;;)
            {
               if (!opStack.empty())
               {
                  topToken = opStack.top();
                  opStack.pop();
                  if (topToken == '(')
                     break;
                  pfixExp.append(BLANK + topToken);
               }
            }
            break;

         case '+' :
         case '-' :
         case '*' :
         case '/' :
         case '%':
            for (;;)
            {
               if (opStack.empty() || opStack.top() == '(' ||
                   (token == '*' || token == '/' || token == '%') &&
                   (opStack.top() == '+' || opStack.top() == '-')) 
               {
                  opStack.push(token);
                  break;
               }
               else
               {
                  topToken = opStack.top();
                  opStack.pop();
                  pfixExp.append(BLANK + token);
               }
            }
            break;

         default :
            pfixExp.append(BLANK + token);
            for(;;)
            {
               if (!isalnum(exp[i+1]))break;
               i++;
               token = exp[i];
               pfixExp.append(1,token);
            }

      }          
   }            
   for (;;)
   {
      if (opStack.empty())
         break;
      topToken = opStack.top();
      opStack.pop();
      if (topToken != '(')
      {
         pfixExp.append(BLANK + topToken);
      }
      else
      {
         cout << "Error in infix notation...\n";
         break;
      }
   }
   return pfixExp;
}

void displayMachineCode(string exp)
{
   Stack here;
   string assembly;
  // if (exp != )
  // { 
//     assembly = "LD";
  cout << "Assembly Code:\n";
  char r;
  char l;
  char temp = '1';
  for (int i = 0; i < exp.length(); i++)
  {
     switch (exp[i])// char push 1, opreand pop2
     {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
           here.push(exp[i]);
        break;
        case ' ':
           break;
           
        case '+':
           assembly = "AD  ";
           r = here.top();
           here.pop();
           l = here.top();
           here.pop();
           cout << "LD  ";
           if (l == 'A' || l == 'B' || l == 'C' || l == 'D' ||
               l == 'E' || l == 'F' || l == 'G' || l == 'H')
              cout << l << endl;
           else
              cout << "TEMP" << l << endl;
           cout << assembly;
           if (r == 'A' || r == 'B' || r == 'C' || r == 'D' ||
               r == 'E' || r == 'F' || r == 'G' || r == 'H')
              cout << r << endl;
           else
              cout << "TEMP" << r << endl;
           cout  << "ST  " << "TEMP" << temp << endl;
           here.push(temp);
           temp++;
           break;          
           
        case '-':
           assembly = "SB  ";
           r = here.top();
           here.pop();
           l = here.top();
           here.pop();
           cout << "LD  ";
           if (l == 'A' || l == 'B' || l == 'C' || l == 'D' ||
               l == 'E' || l == 'F' || l == 'G' || l == 'H')
              cout << l << endl;
           else
              cout << "TEMP" << l << endl;
           cout << assembly;
           if (r == 'A' || r == 'B' || r == 'C' || r == 'D' ||
               r == 'E' || r == 'F' || r == 'G' || r == 'H')
              cout << r << endl;
           else
              cout << "TEMP" << r << endl;
           cout  << "ST  " << "TEMP" << temp << endl;
           here.push(temp);
           temp++;
           break;

           
        case '*':
           assembly = "ML  ";
           r = here.top();
           here.pop();
           l = here.top();
           here.pop();
           cout << "LD  ";
           if (l == 'A' || l == 'B' || l == 'C' || l == 'D' ||
               l == 'E' || l == 'F' || l == 'G' || l == 'H')
              cout << l << endl;
           else
              cout << "TEMP" << l << endl;
           cout << assembly;
           if (r == 'A' || r == 'B' || r == 'C' || r == 'D' ||
               r == 'E' || r == 'F' || r == 'G' || r == 'H')
              cout << r << endl;
           else
              cout << "TEMP" << r << endl;
           cout  << "ST  " << "TEMP" << temp << endl;
           here.push(temp);
           temp++;                             
           break;
           
        case '/':
           assembly = "DV  ";
           r = here.top();
           here.pop();
           l = here.top();
           here.pop();
           cout << "LD  ";
           if (l == 'A' || l == 'B' || l == 'C' || l == 'D' ||
               l == 'E' || l == 'F' || l == 'G' || l == 'H')
              cout << l << endl;
           else
              cout << "TEMP" << l << endl;
           cout << assembly;
           if (r == 'A' || r == 'B' || r == 'C' || r == 'D' ||
               r == 'E' || r == 'F' || r == 'G' || r == 'H')
              cout << r << endl;
           else
              cout << "TEMP" << r << endl;
           
           cout << "ST  " << "TEMP" << temp << endl;
           here.push(temp);
           temp++;
           break;

           
        default:
//           here.push(exp[i]);
           break;
     }
  }
}
//           cout <<  assembly  <<  " " << exp[i] << endl; 

