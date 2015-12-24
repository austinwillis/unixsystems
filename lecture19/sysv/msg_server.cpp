// File: msg_server.cpp
// Server program demonstrating System V message queues

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "msg.h"

using namespace std;

int main(int argc, char *argv[])
{
   message srvmsg, rcdmsg;
   string srvstr, rcdstr;
   time_t curtime;

   srand(getpid());
   srvmsg.type = SRVMSG;

   // Create message queue
   int msgqid = msgget(IPC_PRIVATE, 0600);
   cout << "Message queue id is " << msgqid << endl;

   while(1) {
      // Generate message (time and date)
      curtime = time(NULL);
      srvstr = ctime(&curtime);
      srvstr[srvstr.length()-1] = '\0';
      srvstr.copy(srvmsg.data,MAXLEN-1);

      // In case message is longer than buffer
      // make sure it is zero terminated
      srvmsg.data[MAXLEN-1] = '\0';

      // Send message to client
      cout << "Server sending: " << srvmsg.data << endl;
      msgsnd(msgqid, &srvmsg, MAXLEN, 0);

      // Wait for acknowledgement
      msgrcv(msgqid, &rcdmsg, MAXLEN, CLIMSG, 0);
      rcdstr = rcdmsg.data;
      cout << "Server received: " << rcdstr << endl;

      // If we get END, then end
      if(rcdstr == "END")
         break;
      sleep(rand()%4);
   }

   // Delete the message queue
   msgctl(msgqid, IPC_RMID, 0);

   return 0;
}
