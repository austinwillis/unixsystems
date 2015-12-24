
#include <sys/types.h>
#include <sys/ipc.h>
#include <mqueue.h>

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#define BUFSIZ 256

using namespace std;

int main(int argc, char *argv[])
{
	 cout << "Started client" << endl;
   int count;
   char clidata[BUFSIZ];
   string clistr;

   if(argc != 3) {
      cerr << "Usage: " << argv[0] << " s2cname c2sname" << endl;
      exit(1);
   }

   // open the mqueues
   mqd_t s2cid = mq_open (argv[1], O_RDWR);
   mqd_t c2sid = mq_open (argv[2], O_RDWR);

   for( count=0; count<=4; count++) {

      // Wait for message
      mq_receive(s2cid, clidata, BUFSIZ, 0);
      clistr = clidata;
      cout << "Client received: " << clistr << endl;

      
      // Send acknowledgement back to server
      cout << "Client sending: " << clidata << endl;
      mq_send(c2sid, clidata, BUFSIZ, 1);
   }

   return 0;
}
