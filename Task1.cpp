#include <iostream>
#include <string>
#include <stdio.h>
#include <cctype>

using namespace std;

int CountWords(const char* str) //function for counting the number of words
{
   if (str == NULL)
      return 0;

   bool inSpaces = true;
   int numWords = 0;

   while (*str != '\0')
   {
      if (std::isspace(*str))
      {
         inSpaces = true;
      }
      else if (inSpaces)
      {
         numWords++;
         inSpaces = false;
      }

      ++str;
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