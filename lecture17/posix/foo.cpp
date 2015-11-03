// File: foo.cpp
// Shared resource function

#include <iostream>
#include <unistd.h>

using namespace std;

void foo(int pid)
{
   cout << "BEGIN " << pid << endl;
   sleep(3);
   cout << "END " << pid << endl;
}
