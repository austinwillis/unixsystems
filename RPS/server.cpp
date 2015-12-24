//Austin Willis
//CS375
//Final Project
#include<stdio.h>
#include<string.h>    //strlen
#include<string>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<iostream>
#include<pthread.h> //for threading , link with lpthread
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<sstream>

using namespace std;

void *connection_handler(void *);

int main(int argc , char *argv[])
{
  int socket_desc, c;
    struct sockaddr_in server , client;
    char p1message[6], p2message[6];
    char p1choice[2], p2choice[2];
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    srand (time(NULL));
    int port = rand() % 9000 + 1000;

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( port );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");


    //Listen
    listen(socket_desc , 100);

    while (1) {
   	int tie = 0, p1win = 0, p2win = 0;
	bool stop = false;
	c = sizeof(struct sockaddr_in);
        cout << "Listening on port " << port << endl;
        int p1sockfd = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*)&c);
        if (p1sockfd < 0) {
           cout << "ERROR on accept ";
	   cout << errno << endl;
	}
        else cout << "Player 1 joined" << endl;

        int p2sockfd = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*)&c);
        if (p2sockfd < 0)
          cout << "ERROR on accept";
        else cout << "Player 2 joined" << endl;
	while (!stop) {
        if (recv(p1sockfd , p1message , sizeof(p1message) , 0) > 0 && recv(p2sockfd ,p2message , sizeof(p2message) , 0) > 0) {
    
        if (strcmp(p1message, p2message) == 0 && strcmp(p1message, "READY") == 0) {
        p2message[6] = '\0';
        p2message[6] = '\0';
	

	stringstream p1output;
	stringstream p2output;

        send(p1sockfd, "GO\0", sizeof("GO\0"), 0);
        send(p2sockfd, "GO\0", sizeof("GO\0"), 0);
        recv(p1sockfd , p1choice , sizeof(p1choice) , 0);
	recv(p2sockfd ,p2choice , sizeof(p2choice) , 0);
	    p1output << "Game over, your record was " <<  p1win << '-' << p2win << '-' << tie;
	    p2output << "Game over, your record was " <<  p2win << '-' << p1win << '-' << tie;

        recv(p1sockfd , p1choice , sizeof(p1choice) , 0);
	p1choice[1] = '\0';
	if (strcmp(p1choice, "Q") == 0) {
	    cout << "player quit" << endl;
            send(p1sockfd, p1output.str().c_str(), strlen(p1output.str().c_str()), 0); 
	    stop = true;
        }
	recv(p2sockfd ,p2choice , sizeof(p2choice) , 0);
	p2choice[1] = '\0';
        if (strcmp(p2choice, "Q") == 0) {
	    cout << "player quit" << endl;
            send(p2sockfd, p2output.str().c_str(), strlen(p2output.str().c_str()), 0);
	    stop = true;
	    if (strcmp(p1choice, "Q") != 0) {
            	send(p1sockfd, p1output.str().c_str(), strlen(p1output.str().c_str()), 0); 
	    }
	}
	if (stop && strcmp(p2choice, "Q") != 0) {
            send(p2sockfd, p2output.str().c_str(), sizeof(p2output.str().c_str()), 0); 
	}	
	if (!stop) {

        if (strcmp(p1choice, p2choice) == 0) {
	    cout << "tie" << endl;
            send(p1sockfd, "This round was a tie\0", sizeof("This round was a tie\0"), 0); 
            send(p2sockfd, "This round was a tie\0", sizeof("This round was a tie\0"), 0);
	    tie++;
        }
    
        if (strcmp(p1choice, "R") == 0 && strcmp(p2choice, "P") == 0) {
	    cout << "tie" << endl;
            send(p1sockfd, "You lost\0", sizeof("You lost\0"), 0); 
            send(p2sockfd, "You won\0", sizeof("You won\0"), 0); 
 	    p2win++;     
        }

        if (strcmp(p1choice, "R") == 0 && strcmp(p2choice, "S") == 0) {
	    cout << "player 1 won" << endl;
            send(p2sockfd, "You lost\0", sizeof("You lost\0"), 0); 
            send(p1sockfd, "You won\0", sizeof("You won\0"), 0); 
  	    p1win++;     
        }

        if (strcmp(p1choice, "P") == 0 && strcmp(p2choice, "R") == 0) {
	    cout << "player 1 won" << endl;
            send(p2sockfd, "You lost\0", sizeof("You lost\0"), 0); 
            send(p1sockfd, "You won\0", sizeof("You won\0"), 0); 
  	    p1win++;     
        }

        if (strcmp(p1choice, "P") == 0 && strcmp(p2choice, "S") == 0) {
	    cout << "player 2 won" << endl;
            send(p1sockfd, "You lost\0", sizeof("You lost\0"), 0); 
            send(p2sockfd, "You won\0", sizeof("You won\0"), 0); 
  	    p2win++;     
        }

        if (strcmp(p1choice, "S") == 0 && strcmp(p2choice, "R") == 0) {
	    cout << "player 2 won" << endl;
            send(p1sockfd, "You lost\0", sizeof("You lost\0"), 0); 
            send(p2sockfd, "You won\0", sizeof("You won\0"), 0); 
  	    p2win++;     
        }

        if (strcmp(p1choice, "S") == 0 && strcmp(p2choice, "P") == 0) {
	    cout << "player 1 won" << endl;
            send(p2sockfd, "You lost\0", sizeof("You lost\0"), 0); 
            send(p1sockfd, "You won\0", sizeof("You won\0"), 0); 
  	    p1win++;     
        }
	}
	}
      }
    }
   }
    return 0;
}
