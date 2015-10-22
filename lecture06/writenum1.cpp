#include <unistd.h>
#include <string>
using namespace std;

int main()
{
   string msg = "The value is ";
   int value = 4210752;  // 4210752 == 0x404040
   char nl = '\n';

   write(1, msg.c_str(), msg.length());

   // This displays @@@ since 0x40 is ASCII code for @ character
   write(1, &value, sizeof(value));

   write(1, &nl, sizeof(nl));

   return 0;
}
