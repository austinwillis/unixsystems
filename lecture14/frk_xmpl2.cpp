#include <unistd.h>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
   int count, forkret;
   string indent("");

   cout << "Start of test" << endl;
   cout << "Main Process PID=" << getpid() << endl;
   for(count=1; count<=3; count++) {
      forkret = fork();
      switch(forkret) {
	 case 0:  // C++ ostreams are buffered; endl flushes the buffer
	          // so the entire line will be printed together
	    cout << indent << count << ":  CHILD    ";
	    cout << "PID=" << getpid();
	    cout << "\tPPID=" << getppid() << endl;
	    break;
	 default:
	    cout << indent << count << ":  PARENT   ";
	    cout << "PID=" << getpid();
	    cout << "\tPPID=" << getppid() << endl;
      }
      indent += "   ";
   }
   sleep(1);
   exit(0);
}
