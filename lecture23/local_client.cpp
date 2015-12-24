// File: local_client.cpp
// Client program based on BLP, 4e, page 609

/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    string input;
    char buffer[1024];

    string sockname = "server_socket";

/*  Create the client socket, assign to file descriptor sockfd */

    sockfd = socket(PF_UNIX, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  Name in sockname */

    // ADD CODE HERE
    struct sockaddr *unaddr = (struct sockaddr *)(&address);
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, sockname.c_str());

/*  Connect to the server's socket, make sure to check that it succeeded */

    // ADD CODE HERE
    len = sizeof(struct sockaddr_un);
    result = connect(sockfd, unaddr, len);
    if (result != 0) {
	cout << "connect failed" << endl;
    } 
    

/*  We can now read/write via sockfd.  */

    // Loop until ^D or "end"  ("end" causes server to exit, too)
    while (getline(cin,input)) {
       write(sockfd, input.c_str(), input.length()+1);
       if (input == "end")
	  break;
       read(sockfd, buffer, sizeof(buffer));
       cout << "Client got back: " << buffer << endl;
    }

    cout << "Client is closing socket." << endl;
    close(sockfd);
    exit(0);
}
