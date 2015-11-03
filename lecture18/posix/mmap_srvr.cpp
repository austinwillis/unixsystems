// File: mmap_srvr.cpp
// This program reads data created by the producer.
// The data is passed in a POSIX shared memory segment.

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mmap_com.h"

using namespace std;

int main()
{
    srand((unsigned int)getpid());    

    // Create a dummy name for the memory object
    stringstream sstr;
    sstr << "/MSEG_" << getpid();
    string str_name = sstr.str();
    const char *seg_name = str_name.c_str();
    int mfd = shm_open(seg_name, O_RDWR | O_CREAT, 0600);

    // Extend the object to the required size
    ftruncate(mfd, sizeof(struct shared_use_st));

    // Map the file to a shared memory segment
    void *shared_memory = mmap(
       0, sizeof(struct shared_use_st), 
       PROT_READ | PROT_WRITE, MAP_SHARED,
       mfd, 0
    );

    cout << "Memory attached at " << (unsigned int)shared_memory << endl;
    cout << "Memory object name: " << seg_name << endl;

    // We can close the file descriptor.
    close(mfd);

    // The next portion of the program assigns the shared_memory 
    // segment to shared_stuff, which then prints out any text in 
    // some_text. The loop continues until "end" is found
    // in some_text. The call to sleep forces the child 
    // to sit in its critical section, which makes the server wait.

    struct shared_use_st *shared_stuff = 
       (struct shared_use_st *)shared_memory;
    shared_stuff->written_by_you = 0;
    string message;
    int running = 1;
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

    // Unmap the shared memory segment.
    munmap(shared_memory, sizeof(struct shared_use_st));
    // Delete the name
    shm_unlink(seg_name);

    exit(EXIT_SUCCESS);
}

