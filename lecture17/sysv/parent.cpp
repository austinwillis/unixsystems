// File: parent.cpp
// Example of SysV semaphore usage

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <cstdlib>

using namespace std;
pid_t fpid = -1;
int sem_id = -1;

void foo(int);
void handler (int param) {
   kill(fpid,SIGTERM); 
   struct sembuf sop;
   semop(sem_id, &sop, IPC_RMID);
   exit(0);
}

int main()
{
   // Create the semaphore
   sem_id = semget(IPC_PRIVATE, 1, 0600);

   // initialize it to 1 so that it is initially available
   semctl(sem_id, 0, SETVAL, 1);

   fpid = fork();

   if (fpid == 0) {
      stringstream argstr;
      argstr << sem_id;
      // Child
      execl("child", "child", argstr.str().c_str(), (char *)0);
      cerr << "child exec failed, exiting" << endl;
      exit (1);
   }

   struct sembuf sops_acquire = {0, -1, SEM_UNDO};
   struct sembuf sops_release = {0, 1, SEM_UNDO};

   void (*prev_handler)(int);

   prev_handler = signal (SIGINT,(void (*)(int))handler);

   int mypid = getpid();

   while(true) {
      semop(sem_id, &sops_acquire, 1);
      foo(mypid);
      semop(sem_id, &sops_release, 1);

      // do something to allow other processes to acquire semaphore
      sleep(1);

   }
}
