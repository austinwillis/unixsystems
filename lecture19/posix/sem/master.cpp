#include <sys/types.h>
#include <sys/ipc.h>
#include <mqueue.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
sem_t *sem;
sem_t *sem2;

using namespace std;

#define BUFSIZ 256

int main(int argc, char *argv[])
{
   string sem_name = "/uppersem";
   string sem2_name = "/uppersem2";
   string mem = "/share";
   string srvstr, rcdstr;
   char srvdata[BUFSIZ], rcvdata[BUFSIZ];
   time_t curtime;
	 int pid;
   sem = sem_open(sem_name.c_str(), O_CREAT | O_EXCL, 0600, 1);
   sem = sem_open(sem2_name.c_str(), O_CREAT | O_EXCL, 0600, 1);

   srand(getpid());

   // Create message queue
   stringstream sstr;
   sstr << "/SRV2CLI_" << getpid();
   string str_name = sstr.str();
   const char *s2c_name = str_name.c_str();
   stringstream sstr2;
   sstr2 << "/CLI2SRV_" << getpid();
   string str2_name = sstr2.str();
   const char *c2s_name = str2_name.c_str();

   struct mq_attr attr;
   attr.mq_flags = 0;
   attr.mq_maxmsg = 1;
   attr.mq_msgsize = BUFSIZ;
   attr.mq_curmsgs = 0;

   pid = fork();
   if (pid == 0) {
     execl("reverse", "reverse", s2c_name, sem_name.c_str(), sem2_name.c_str(), (char *) 0);
   }

   pid = fork();
   if (pid == 0) {
	execl("upper", "upper", sem_name.c_str(), sem2_name.c_str(), (char *) 0);
   }

   mqd_t s2cid = mq_open (s2c_name, O_RDWR | O_CREAT, 0600, &attr);

   cout << "Server to Client message queue name is " << s2c_name << endl;
   cout << "Client to Server message queue name is " << c2s_name << endl;

   while(1) {
      // Generate message (time and date)
      cout << ">";
      cin >> srvstr;
			//cin >> srvstr;
      srvstr.push_back('\0');
      srvstr.copy(srvdata, srvstr.length());

      // In case message is longer than buffer
      // make sure it is zero terminated
      srvdata[BUFSIZ-1] = '\0';

      // Send message to client
      mq_send(s2cid, srvdata, BUFSIZ, 1);

      // If we get END, then end
      if(rcdstr == "END")
         break;
      sleep(rand()%4);
   }

   // Delete the message queue
   mq_close(s2cid);
   mq_unlink(s2c_name);

   return 0;
}
