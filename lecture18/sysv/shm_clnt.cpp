// File: shm_clnt.cpp
// The second program is the producer and allows us to enter data 
// for consumers.  It's very similar to shm_srvr.cpp and looks like this.

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>  // strncpy

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shm_com.h"

using namespace std;

int main(int argc, char *argv[])
{
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    string message;
    int shmid;

    if(argc != 2) {
       cerr << "usage: shm_clnt shmid\n";
       exit(5);
    }
    shmid = atoi(argv[1]);
    // Use shmat to attach an existing SysV shared memory object.
    // The object was created by the server program.
    // NEW CODE HERE 

    cout << "Memory attached at " << (unsigned int)shared_memory << endl;

    shared_stuff = (struct shared_use_st *)shared_memory;
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

    // Detach the shared segment
    // NEW CODE HERE 

    exit(EXIT_SUCCESS);
}
