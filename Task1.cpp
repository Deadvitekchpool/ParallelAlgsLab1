#include <iostream>
#include <string>
#include <stdio.h>
#include <cctype>

using namespace std;

int CountWords(const char* str) //function for counting the number of words
{
   if (str == NULL) //if no string passed then we have 0 words
      return 0;

   bool inSpaces = true; //flag for space indication
   int numWords = 0; // words counter

   while (*str != '\0') //looping till the end of the string is reached
   {
      if (std::isspace(*str)) //set the flag to true if current char is space
      {
         inSpaces = true;
      }
      else if (inSpaces) //turn off the flag and increase the number of words
      {
         numWords++;
         inSpaces = false;
      }

      ++str; //iterating though each character of the string
   }

   return numWords;
}

int main(int argc, char** argv){ 
    if (argc > 1) { 
        printf("Given string has %d words\n", CountWords(argv[1]));
    }
    else {
        cout << "No arguments given" << endl;
    }
    return 0;
}