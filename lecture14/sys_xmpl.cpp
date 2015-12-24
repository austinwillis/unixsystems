#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
   string command;

   cout << "Welcome to vvssh (Very Very Simple Shell)!" << endl;
   cout << "Enter <CTRL>-D to exit." << endl;
   cout << "% ";
   while(getline(cin, command)) {
      system(command.c_str());
      cout << "% ";
   }
   return 0;
}
