// File: shm_srvr.cpp
// Our first program is a consumer. After the headers, the shared memory 
// segment (the size of our shared memory structure) is created with a 
// call to shmget.

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shm_com.h"

using namespace std;

int main()
{
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    string message;
    int shmid;

    srand((unsigned int)getpid());    

    // Allocate shared memory segment
    shmid = shmget(IPC_PRIVATE, sizeof(struct shared_use_st), 0666);

    // We now make the shared memory accessible to the program. 
    shared_memory = shmat(shmid, (void *)0, 0);

    cout << "Shared memory id is " << shmid << endl;
    cout << "Memory attached at " << (unsigned int)shared_memory << endl;

    // The next portion of the program assigns the shared_memory 
    // segment to shared_stuff, which then prints out any text in 
    // written_by_you. The loop continues until end is found
    // in written_by_you. The call to sleep forces the consumer 
    // to sit in its critical section, which makes the producer wait.

    shared_stuff = (struct shared_use_st *)shared_memory;
    shared_stuff->written_by_you = 0;
    while(running) {
        if (shared_stuff->written_by_you) {
            message = shared_stuff->some_text;
            cout << "You wrote: " << message << endl;
            // make the other process wait for us ! 
            sleep( rand() % 4 );
            shared_stuff->written_by_you = 0;
            if (message == "end") {
                running = 0;
            }
        }
        // Use a pair of semaphores for two-way synchronization
        // and avoid the following sleep for better performance.
	sleep(1);
    }

    // Lastly, the shared memory is detached and then deleted.
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
}

