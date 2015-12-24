// File: local_server.cpp
// Server program based on BLP, 4e, pages 610-611

/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
    int read_count, server_sockfd, client_sockfd;
    socklen_t server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;
    char buffer[1024];

    string sockname = "server_socket";
    const char *sockname_cstr = sockname.c_str();

/*  Remove any old socket.  */
    unlink(sockname_cstr);


/*  Create an unamed socket for the server, 
    assign to file descriptor server_sockfd */

    server_sockfd = socket(PF_UNIX, SOCK_STREAM, 0);

/*  Name the socket, as agreed with client.  Name in sockname.  */

    struct sockaddr *unserver = (struct sockaddr *)(&server_address);
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, sockname.c_str());
    struct sockaddr *unclient = (struct sockaddr *)(&client_address);
    client_address.sun_family = AF_UNIX;
    strcpy(client_address.sun_path, sockname.c_str());

/*  Create a connection queue and wait for clients.  */

    // ADD CODE HERE
    socklen_t len = sizeof(struct sockaddr_un);
    bind(server_sockfd, unserver, len);
    listen(server_sockfd, 5);

    bool done = false;

    // Loop until a client sends "end"
    while(!done) {

        cout << "server waiting" << endl;

/*  Accept a connection, assign to file descriptor client_sockfd.  */

        // ADD CODE HERE
	client_sockfd = accept(server_sockfd, unclient, &len);

/*  We can now read/write to client on client_sockfd.  */

	// Loop until client closes socket or sends "end"
        while(true) {
           read_count = read(client_sockfd, buffer, sizeof(buffer));
           if(read_count == 0)
              break;
           cout << "Server: " << buffer << endl;
	   if (strcmp(buffer, "end") == 0)
	   {
	      done = true;
	      break;
	   }
           write(client_sockfd, "ok", 3);
        }
        cout << "Server is closing socket." << endl;
        close(client_sockfd);
    }

/* Remove the socket */
    unlink(sockname_cstr);
}
