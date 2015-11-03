// File: child.cpp
// Example of SysV semaphore usage

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

using namespace std;

void foo(int);

int main(int argc, char *argv[])
{
   // SysV just needs to know the semaphore id to do the operations
   int sem_id = atoi(argv[1]);

   int mypid = getpid();

   struct sembuf sops_acquire = {0, -1, SEM_UNDO};
   struct sembuf sops_release = {0, 1, SEM_UNDO};

   while (true) {
      // acquire semaphore here
      semop(sem_id, &sops_acquire, 1);
      foo(mypid);
      semop(sem_id, &sops_release, 1);
      // release semaphore here

      // do something to allow other processes to acquire semaphore
      sleep(1);
   }
}
