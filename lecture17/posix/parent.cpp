// File: parent.cpp
// Demonstrates using named POSIX semaphores

#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
pid_t fpid = -1;
sem_t *sem;

using namespace std;

void foo(int);
void handler (int param) {
   kill(fpid,SIGTERM); 
   sem_close(sem);
   exit(0);
}

int main()
{
   string sem_name = "/cs375_sem1";
   // Create the named semaphore
   // initialize it to 1 so that it is initially available
   sem = sem_open(sem_name.c_str(), O_CREAT | O_EXCL, 0600, 1);
   fpid = fork();

   if (fpid == 0) {
      // Child
      execl("child", "child", sem_name.c_str(), (char *)0);
      cerr << "child exec failed, exiting" << endl;
      exit(1);
   }

   void (*prev_handler)(int);

   prev_handler = signal (SIGINT,(void (*)(int))handler);

   int mypid = getpid();
   sem = sem_open(sem_name.c_str(), 0);
   while(true) {
      sem_wait(sem);
      foo(mypid);
      sem_post(sem);

      // do something to allow other processes to acquire semaphore
      sleep(1);
   }
}
