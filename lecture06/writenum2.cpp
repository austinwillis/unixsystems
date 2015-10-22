#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
   string msg = "The value is ";
   int value = 4210752;  // 4210752 == 0x404040
   char nl = '\n';

   write(1, msg.c_str(), msg.length());

   // Format value as decimal number
   ostringstream svalue;
   svalue << value;
   write(1, svalue.str().c_str(), svalue.str().length());

   write(1, &nl, sizeof(nl));

   return 0;
}
