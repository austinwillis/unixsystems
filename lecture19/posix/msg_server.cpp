#include <sys/types.h>
#include <sys/ipc.h>
#include <mqueue.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

#define BUFSIZ 256

int main(int argc, char *argv[])
{
   string srvstr, rcdstr;
   char srvdata[BUFSIZ], rcvdata[BUFSIZ];
   time_t curtime;
	 int pid;

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
		  execl("msg_client", "msg_client", s2c_name, c2s_name, (char *) 0);
   }

   mqd_t s2cid = mq_open (s2c_name, O_RDWR | O_CREAT, 0600, &attr);
   mqd_t c2sid = mq_open (c2s_name, O_RDWR | O_CREAT, 0600, &attr);

   cout << "Server to Client message queue name is " << s2c_name << endl;
   cout << "Client to Server message queue name is " << c2s_name << endl;

   while(1) {
      // Generate message (time and date)
      curtime = time(NULL);
      cout << ">";
      cin >> srvstr;
			//cin >> srvstr;
      srvstr.push_back('\0');
      srvstr.copy(srvdata, srvstr.length());

      // In case message is longer than buffer
      // make sure it is zero terminated
      srvdata[BUFSIZ-1] = '\0';

      // Send message to client
      cout << "Server sending: " << srvdata << endl;
      mq_send(s2cid, srvdata, BUFSIZ, 1);

      // Wait for acknowledgement
      mq_receive(c2sid, rcvdata, BUFSIZ, 0);
      rcdstr = rcvdata;
      cout << "Server received: " << rcdstr << endl;

      // If we get END, then end
      if(rcdstr == "END")
         break;
      sleep(rand()%4);
   }

   // Delete the message queue
   mq_close(s2cid);
   mq_unlink(s2c_name);
   mq_close(c2sid);
   mq_unlink(c2s_name);

   return 0;
}
