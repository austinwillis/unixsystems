#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <mqueue.h>
#include <sys/mman.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "mmap_com.h"
sem_t *sem;
sem_t *sem2;
#define BUFSIZ 256

using namespace std;

int main(int argc, char *argv[])
{
   int count;
   //int shm_fd;
   //shm_fd = shm_open(argv[3], O_RDWR , 0600);
   char clidata[BUFSIZ];
   string clistr;

   if(argc != 4) {
      cerr << "Usage: " << argv[0] << " queue semaphore semaphore" << endl;
      exit(1);
   }

   // open the mqueues
   mqd_t s2cid = mq_open (argv[1], O_RDWR);

   sem = sem_open(argv[2], 0);
   sem2 = sem_open(argv[3], 0);
   //void *shared_memory = mmap(
   //     0, sizeof(struct shared_use_st), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
   while(1) {
      //wait semaphore
      sem_wait(sem);

      // Wait for message
      mq_receive(s2cid, clidata, BUFSIZ, 0);
      clistr = clidata;
      cout << clistr << endl;
      cout << "something" << endl;
      
      //put message in shared memory
      //const char *memory = (char *)shared_memory;
      //memory = clistr.c_str();

      sem_post(sem2);
      // Send acknowledgement back to server
   }

   return 0;
}
