#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <mqueue.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "mmap_com.h"
#define BUFSIZ 256
using namespace std;
sem_t *sem;
sem_t *sem2;
mqd_t s2cid;
bool end = false;
string srvstr, rcdstr;
char srvdata[BUFSIZ];

void handler(int param) {
      cout << ">";
      getline(cin, srvstr);

      if (cin.eof() == 1) {
	end = true;
        srvstr = "shutting down";
      }
                        //cin >> srvstr;
      srvstr.push_back('\0');
      srvstr.copy(srvdata, srvstr.length());

      // In case message is longer than buffer
      // make sure it is zero terminated
      srvdata[BUFSIZ-1] = '\0';
      mq_send(s2cid, srvdata, BUFSIZ, 1);

      // If we get END, then end
}

int main(int argc, char *argv[])
{
   string sem_name = "/uppersem";
   string sem2_name = "/uppersem2";
   string mem = "/share";
   time_t curtime;
	 int pid;

   //create semaphores
   sem = sem_open(sem_name.c_str(), O_CREAT | O_EXCL, 0600, 1);
   sem = sem_open(sem2_name.c_str(), O_CREAT | O_EXCL, 0600, 1);

   srand(getpid());

   // Create message queue
   stringstream sstr;
   sstr << "/SRV2CLI_" << getpid();
   string str_name = sstr.str();
   const char *s2c_name = str_name.c_str();

   //create shared memory
   string memname = "/share";
    int mfd = shm_open(memname.c_str(), O_RDWR | O_CREAT, 0600);

    // Extend the object to the required size
    ftruncate(mfd, sizeof(struct shared_use_st));

    // Map the file to a shared memory segment
    void *shared_memory = mmap(
       0, sizeof(struct shared_use_st),
       PROT_READ | PROT_WRITE, MAP_SHARED,
       mfd, 0
    ); 

    close(mfd);

   struct mq_attr attr;
   attr.mq_flags = 0;
   attr.mq_maxmsg = 1;
   attr.mq_msgsize = BUFSIZ;
   attr.mq_curmsgs = 0;

   pid = fork();
   if (pid == 0) {
     execl("reverse", "reverse", s2c_name, sem_name.c_str(), sem2_name.c_str(), memname.c_str(), (char *) 0);
   }

   pid = fork();
   if (pid == 0) {
	execl("upper", "upper", sem_name.c_str(), sem2_name.c_str(), memname.c_str(), (char *) 0);
   }

   s2cid = mq_open (s2c_name, O_RDWR | O_CREAT, 0600, &attr);

   cout << "Server to Client message queue name is " << s2c_name << endl;

   signal(SIGUSR1, handler);

   raise(SIGUSR1);

   while(end) {
	pause();
   }

   // Delete the message queue
   sem_close(sem);
   sem_close(sem2);
   mq_close(s2cid);
   mq_unlink(s2c_name);
   munmap(shared_memory, sizeof(struct shared_use_st));
   shm_unlink(memname.c_str());
   return 0;
}
