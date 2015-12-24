//Austin Willis
//CS375
//Project 6
#include <sys/types.h>
#include <string.h>
#include <algorithm>
#include <sys/ipc.h>
#include <mqueue.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "mmap_com.h"
sem_t *sem;
sem_t *sem2;

using namespace std;

#define BUFSIZ 256

int main(int argc, char *argv[]) {
    pid_t pid = getppid();
    sem = sem_open(argv[1], 0);
    sem2 = sem_open(argv[2], 0);
    sem_post(sem);

    int mfd = shm_open(argv[3], O_RDWR | O_CREAT, 0600);

    // Map the file to a shared memory segment
    void *shared_memory = mmap(
       0, sizeof(struct shared_use_st),
       PROT_READ | PROT_WRITE, MAP_SHARED,
       mfd, 0
    );

   struct shared_use_st *shared_stuff =
       (struct shared_use_st *)shared_memory;
    shared_stuff->written_by_you = 0;
    string message;
    bool end = false;

    while (1) {
    
   	sem_wait(sem2);
	if (shared_stuff->written_by_you) {
	    if (strcmp(shared_stuff->some_text, "shutting down") == 0) {
		end = true;
	    } else {
	    message = shared_stuff->some_text;
	    transform(message.begin(), message.end(),message.begin(), ::toupper);
    	    cout << message << endl;
	    shared_stuff->written_by_you = 0;
            }
        }
	kill(pid, SIGUSR1);
	
    	sem_post(sem);
	if (end)
	   break;
    }
    sem_close(sem);
    sem_close(sem2);
   munmap(shared_memory, sizeof(struct shared_use_st));
   shm_unlink(argv[3]);
    return 0;
}
