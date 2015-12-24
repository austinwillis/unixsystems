// modification of program on pp 475-476 of BLP,4e

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
   int pid, count, exit_code;
   string msg;

   cout << "fork example program starting" << endl;
   pid = fork();
   switch(pid) {
      case -1:
         cerr << "fork failed" << endl;
         exit(1);
      case 0:
         msg = "This is the child.";
         count = 5;
         exit_code = 37;
         break;
      default:
         msg = "This is the parent.";
         count = 3;
         exit_code = 0;
         break;
   }

   for(; count > 0; count--) {
      cout << msg << "(PID = " << getpid() << ")" << endl;
      sleep(1);
   }

   if(pid != 0) { // parent process
      int status;
      pid = wait(&status);
      cout << "Child has finished (PID = " << pid << ")" << endl;
      if(WIFEXITED(status))
         cout << "Child exit status: " << WEXITSTATUS(status) << endl;
      else
         cout << "Child exitted abnormally." << endl;
   }

   exit(exit_code);
}
