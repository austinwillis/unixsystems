// File: zmb_xmpl2.cpp
// Program that avoids creating a zombie process by creating an
// intermediate parent process whose exit causes the child process
// to be adopted by init.

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
   int pid;

   if ((pid = fork()) == 0) {		// first child
      cout << "This is the first child; forking the second child" << endl;
      if ( (pid = fork()) == 0) {	// second child
	 // our parent becomes init when first child exits
	 cout << "This is the second child.  Just sleep for the demo" << endl;
	 sleep (10);
	 cout << "Second child attempting to exit." << endl;
	 exit (0);
      }
      cout << "First child sleeping for a little while" << endl;
      sleep(3);
      cout << "First child exiting." << endl;
      // first child, so exit.  Second child is adopted by init
      exit(0);
   }
   
   // this is the parent
   cout << "This is the parent.  Wait for the first child to exit." << endl;
   waitpid(pid, NULL, 0);   // wait for first child
   // we're the parent – go on and do our own thing
   // we don't have to worry about the second child
   cout << "First child has exited." << endl;
   cout << "Parent going into an infinite loop" << endl;
   while (true);
}
