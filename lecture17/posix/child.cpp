// File: child.cpp
// Demonstrates using named POSIX semaphores

#include <semaphore.h>
#include <iostream>
#include <unistd.h>

using namespace std;

void foo(int);

int main(int argc, char *argv[])
{
   int mypid = getpid();

   // Posix requires an open to get the semaphore pointer.
   sem_t *sem = sem_open(argv[1], 0);

   while (true) {
      // acquire semaphore here
      sem_wait(sem);
      foo(mypid);
      // release semaphore here
      sem_post(sem);
      // do something to allow other processes to acquire semaphore
      sleep(1);
   }
}
