#include <sys/types.h>
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
   //int shm_fd;
   //shm_fd = shm_open(argv[2], O_RDWR , 0600);
   //void *shared_memory = mmap(
//	0, sizeof(struct shared_use_st), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sem = sem_open(argv[1], 0);
    sem2 = sem_open(argv[2], 0);
    sem_post(sem);
    while (1) {
    
   	sem_wait(sem2);
	//char *buffer = (char *)shared_memory;
    	cout << "upper" << endl;

    	sem_post(sem);
    }
}
