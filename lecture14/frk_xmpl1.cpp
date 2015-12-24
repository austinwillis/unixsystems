#include <unistd.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
   int forkret;

   cout << "First fork example" << endl;
   cout << "Start of test" << endl;
   forkret = fork();
   cout << "fork() returned " << forkret << endl;
   exit(0);
}
