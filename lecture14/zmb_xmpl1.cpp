// File: zmb_xmpl1.cpp
// Program that creates a zombie process

#include <unistd.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
   int forkret;

   cout << "Create a zombie process" << endl;
   forkret = fork();
   switch(forkret) {
      case 0:  // C++ ostreams are buffered; endl flushes the buffer
	       // so the entire line will be printed together
	 cout << "This is the child process. Sleep awhile." << endl;
	 sleep (10);
	 cout << "Child trying to exit" << endl;
	 exit (0);
	 break;
      default:
	 cout << "This is the parent" << endl;
	 cout << "Going into an infinite loop" << endl;
	 cout << "To see the zombie use \"ps aux | grep xmp1\" in another terminal" << endl;
	 cout << "Use Ctrl-C to terminate program" << endl;
	 while(true);
   }
}
