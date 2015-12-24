#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
   int pid, status;
   string command;

   cout << "Welcome to vssh (Very Simple Shell)!" << endl;
   cout << "Enter <CTRL>-D to exit." << endl;
   cout << "% ";
   while(getline(cin, command)) {
      pid = fork();
      switch (pid) {
         case -1:
	    cerr << "fork error" << endl;
	    break;
         case 0:
            // child
            // we only handle commands with no arguments
            // to handle arguments we need to break the command
            // into words, stuff the words into an array and use
            // execvp
	    execlp(command.c_str(), command.c_str(), (char *)0);
	    break;
         default:
            // parent
            // wait until child finishes
            // to run a process "in the background" just don't call wait
	    wait(&status);
	    break;
      }
      cout << "% ";
   }
   return 0;
}
