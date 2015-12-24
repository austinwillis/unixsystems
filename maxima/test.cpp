#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <regex>
#include <vector>

int p2c[2], c2p[2];
using namespace std;
vector<string> split(const string &s, char delim);
vector<string> &split(const string &s, char delim, vector<string> &elems);
string parse(string s);

int main(int argc, char *argv[]) {
	char buffer[200];
  ssize_t bytesRead;
  pid_t childPid;
	string input;

  pipe(p2c);
  pipe(c2p);
  bool cmd;
  if (argc < 2) {
    cmd = false;
  } else {
    cmd = true;
  }
  childPid = fork();
  if(childPid == -1){
    perror("fork");
    exit(-1);
  }else if(childPid == 0){
		close(p2c[1]);
		close(c2p[0]);
		dup2(p2c[0],0);
		dup2(c2p[1],1);
		execlp("maxima", "maxima", "-q", (char *)NULL);
		perror("execlp");
		cerr << "Failed to execute maxima" << endl;
    exit(1);
  } else {
		string line;
		close(p2c[0]);
		close(c2p[1]);
		write(p2c[1], "display2d:false;\n", strlen("display2d:false;\n"));
		sleep(2);
		read(c2p[0], buffer, sizeof(buffer)-1);
		memset( buffer, '\0', sizeof(buffer));
		if (cmd) {
			for (int i = 1; i < argc; i++) {
			  char str[strlen(argv[i])+10];
        strcpy(str, "expand(");
        strcat(str, argv[i]);
        strcat(str, ");\n");
        write(p2c[1], str, strlen(str));
        sleep(2);
        read(c2p[0], buffer, sizeof(buffer)-1);
        line = string(buffer);
				cout << argv[i] << " = " << parse(line) << endl;
        memset( buffer, '\0', sizeof(buffer));	
			}
		} else {
		while(input != "quit") {
			cout << ">";
			cin >> input;
			if (input != "quit") {
				char str[strlen(input.c_str())+10];
				strcpy(str, "expand(");
				strcat(str, input.c_str());
				strcat(str, ");\n");
				write(p2c[1], str, strlen(str));
				sleep(2);
				read(c2p[0], buffer, sizeof(buffer)-1);
				line = string(buffer);
        cout << parse(line) << endl;
				memset( buffer, '\0', sizeof(buffer));
			}
		}
		}
		write(p2c[1], "quit();\n", strlen("quit();\n"));
    return 0;
	}
}	

string parse(string s) {
	vector<string> lines = split(s, '\n');
	string line = lines[1];
	line.erase(0,5);
  return regex_replace(line,regex("\\s+"), "");
}	


vector<string> &split(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}


vector<string> split(const string &s, char delim) {
  vector<string> elems;
  split(s, delim, elems);
  return elems;
}
