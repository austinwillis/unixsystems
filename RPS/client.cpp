//Austin Willis
//CS375
//Final Project
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "Usage: client hostname port";
        return(-1);
    }
    int read_size;
    int SocketD = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *host;
    host = gethostbyname(argv[1]);
    sockaddr_in SockAddr;
    SockAddr.sin_port=htons(atoi(argv[2]));
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    if (!connect(SocketD, (sockaddr*)&SockAddr, sizeof(SockAddr))) {
    string input;
    char go[3], choice[2], result[200], end[5];
    bool stop = false;
    cout << "Waiting for another player to join" << endl;
    while (!stop) {
        send(SocketD,"READY\0",sizeof("READY\0"),0);
        recv(SocketD,go,sizeof(go),0);
        go[2] = '\0';
        if (strcmp(go, "GO") == 0) {
    	    cout << "Enter Rock, Paper, Scissors (STOP to quit)" << endl; 
    	    cin >> input;
	    if (strcmp(input.c_str(), "STOP") == 0) {
		choice[0] = 'Q';
		choice[1] = '\0';
    	    	send(SocketD, choice, sizeof(choice), 0);
    	    	cout << "Waiting for other player" << endl;
    	    	recv(SocketD, result, sizeof(result), 0);
    	    	recv(SocketD, result, sizeof(result), 0);
	    	result[199] = '\0';
    	    	cout << result << endl;
		stop = true;
 	    } else {
    	    char c = toupper(input.c_str()[0]);
	    if (c == 'R' || c == 'P' || c == 'S') {
    	    	choice[0] = c;
    	    	choice[1] = '\0';
    	    	send(SocketD, choice, sizeof(choice), 0);
    	    	cout << "Waiting for other player" << endl;
    	    	recv(SocketD, result, sizeof(result), 0);
    	    	recv(SocketD, result, sizeof(result), 0);
		string r = string(result);
		if (strcmp(r.substr(0, 4).c_str(), "Game") == 0) {
    	    	cout << result << endl;
		stop = true;
		} else {
    	    	   cout << result << endl;
		}
	    }
	    }
    }
    }
    } else cout << "Could not connect to server. Try again later." << endl;
    close(SocketD);
}
