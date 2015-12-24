// File: getsrv.cpp
// Program that demostrates obtaining server information
// by name and by port number
// Usage: getsrv serv_name serv_port

#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
   if (argc != 3)
   {
      cerr << "Usage: " << argv[0] << " serv_name serv_port" << endl;
      exit(1);
   }

   struct servent *s_ent = getservbyname(argv[1],"tcp");
   cout << "Get service info by name: " << argv[1] << endl;
   cout << "Name: " << s_ent->s_name << endl;
   char **s_aliases = s_ent->s_aliases;
   while(*s_aliases) {
      cout << "   alias: " << *s_aliases << endl;
      s_aliases++;
   }
   cout << "Port: " << ntohs(s_ent->s_port) << endl;
   cout << "Proto: " << s_ent->s_proto << endl;

   int port = atoi(argv[2]);
   s_ent = getservbyport(htons(port), "tcp");
   cout << "\nGet service info by port number: " << argv[2] << endl;
   cout << "Name: " << s_ent->s_name << endl;
   s_aliases = s_ent->s_aliases;
   while(*s_aliases) {
      cout << "   alias: " << *s_aliases << endl;
      s_aliases++;
   }
   cout << "Port: " << ntohs(s_ent->s_port) << endl;
   cout << "Proto: " << s_ent->s_proto << endl;
}
