// File: mmap_client.cpp
// This program is the producer and creates data for the consumer.
// The data is passed in a POSIX shared memory segment.

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring> // strncpy
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "mmap_com.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Use shm_open() to open an existing POSIX shared memory object.
    // The object was created by the server program.
    // NEW CODE HERE 
    

    // Now use mmap() to map the shared memory object into local
    // process memory address space.
    // FILL IN ARGUMENTS IN FOLLOWING CALL TO MMAP
    void *shared_memory = mmap( /* ... */ );

    cout << "Memory attached at " << (unsigned int)shared_memory << endl;

    // Cast the pointer to a pointer of the proper type.
    struct shared_use_st *shared_stuff = 
         (struct shared_use_st *)shared_memory;
    int running = 1;
    string message;
    while(running) {
        while(shared_stuff->written_by_you == 1) {
            sleep(1);            
            cout << "waiting for server ..." << endl;
        }
        cout << "Enter some text: ";
        getline(cin, message);
        
        strncpy(shared_stuff->some_text, message.c_str(), TEXT_SZ);
        shared_stuff->written_by_you = 1;

        if (message == "end") {
                running = 0;
        }
    }

    // Unmap the shared segment
    // NEW CODE HERE 

    exit(EXIT_SUCCESS);
}
