//Austin Willis
//CS375
//Project 6
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <mqueue.h>
#include <sys/mman.h>
#include <string.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "mmap_com.h"
sem_t *sem;
sem_t *sem2;
char str[256],rstr[256];
int i,n;
#define BUFSIZ 256

using namespace std;

void reverseChar(char* str) {
    const size_t len = strlen(str);

    for(size_t i=0; i<len/2; i++)
        swap(str[i], str[len-i-1]);
}

int main(int argc, char *argv[])
{
   int count;
   //int shm_fd;
   //shm_fd = shm_open(argv[3], O_RDWR , 0600);
   char clidata[BUFSIZ];
   string clistr;

   if(argc != 5) {
      cerr << "Usage: " << argv[0] << " queue semaphore semaphore memory" << endl;
      exit(1);
   }

   // open the mqueues
   mqd_t s2cid = mq_open (argv[1], O_RDWR);

   sem = sem_open(argv[2], 0);
   sem2 = sem_open(argv[3], 0);

    int mfd = shm_open(argv[4], O_RDWR | O_CREAT, 0600);

    // Map the file to a shared memory segment
    void *shared_memory = mmap(
       0, sizeof(struct shared_use_st),
       PROT_READ | PROT_WRITE, MAP_SHARED,
       mfd, 0
    );

   struct shared_use_st *shared_stuff =
       (struct shared_use_st *)shared_memory;
    shared_stuff->written_by_you = 0;
    bool end = false;

   while(1) {
      //wait semaphore
      sem_wait(sem);
      string rev;
      // Wait for message
      mq_receive(s2cid, clidata, BUFSIZ, 0);
      if (strcmp(clidata, "shutting down") == 0) {
	  end = true;
	  clistr = clidata;
          strcpy(shared_stuff->some_text, clistr.c_str()); 
          shared_stuff->written_by_you = 1;
      } else {
        reverseChar(clidata);
        clistr = clidata;
        strcpy(shared_stuff->some_text, clistr.c_str()); 
        shared_stuff->written_by_you = 1;
      }
      //put message in shared memory
      //const char *memory = (char *)shared_memory;
      //memory = clistr.c_str();

      sem_post(sem2);
      // Send acknowledgement back to server
      if (end)
	break;
   }

   sem_close(sem);
   sem_close(sem2);
   mq_close(s2cid);
   munmap(shared_memory, sizeof(struct shared_use_st));
   shm_unlink(argv[4]);
   return 0;
}
