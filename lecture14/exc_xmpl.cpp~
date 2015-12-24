#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{

   cout << "Before the call to exec." << endl;
   execl("/bin/echo","echo","hello","world!",(char *)0);
   cout << "After the call to exec." << endl;
   cout << "You will not see this output unless the call" << endl;
   cout << "to execl fails." << endl;
   return 0;
}
