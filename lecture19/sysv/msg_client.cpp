// File: msg_client.cpp
// Client program demonstrating System V message queues

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "msg.h"

using namespace std;

int main(int argc, char *argv[])
{
   int count;
   message climsg;
   string clistr;

   if(argc != 2) {
      cerr << "Usage: " << argv[0] << " msgqid" << endl;
      exit(1);
   }

   int msgqid = atoi(argv[1]);

   for( count=0; count<=4; count++) {

      // Wait for message
      msgrcv(msgqid, &climsg, MAXLEN, SRVMSG, 0);
      clistr = climsg.data;
      cout << "Client received: " << clistr << endl;

      // Send acknowledgement back to server
      climsg.type = CLIMSG;
      if (count < 4) {
         clistr = "OK";
         clistr.push_back('\0');
         clistr.copy(climsg.data, clistr.length());
      }
      else {
         clistr = "END";
         clistr.push_back('\0');
         clistr.copy(climsg.data, clistr.length());
      }
      cout << "Client sending: " << climsg.data << endl;
      msgsnd(msgqid, &climsg, MAXLEN, 0);
   }

   return 0;
}
