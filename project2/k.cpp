//Austin Willis
//CS375 Project 2
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;


void printfile(const char *str);
bool E, n, s, noarg = false;

int main(int argc, char *argv[]) {
int option;
char *value;
//Get command line options
while ((option = getopt(argc, argv,"Ens")) != -1) {
        switch (option) {
             case 'E' : 
		E = true;
		break;
             case 'n' :
		n = true;
		break;
             case 's' :
		s = true;
		break;
             default:
                 exit(EXIT_FAILURE);
        }
    }
    bool print = false;
    FILE *file;
    //Print each command line argument that was a file
    //Set print to true if a file was entered
    for (int i = 1; i < argc; i++) {
	if (argv[i][0] != '-') {
		if ((file = fopen(argv[i], "r"))) {
		    print = true;
		    fclose(file);
		    printfile(argv[i]);
		}
	}
    }
    //Accept input from stdin if no file was entered
    if (!print) {
        noarg = true;
        printfile(argv[0]);
    }

return 0;
}

void printfile(const char *str) {
   //Open file if one was entered
   if (!noarg)
	freopen(str, "rb", stdin);
   //String to check if multiple blank lines are read
   string prevline;
   string line;
   int i = 1;
   //Get lines from file or stdin
   while(getline(cin, line)) {
       if (n) {
           printf("%6d  %s", i++, line.c_str());
	   if (E) {
		    if (!s || (line.compare(prevline) != 0 && line.compare("\n") != 0)) {
	               printf("$\n");
		    }
           } else {
		    if (!s || (line.compare(prevline) != 0 && line.compare("\n") != 0)) {
	               printf("\n");
		    }
	   }
	} else {
	   printf("%s", line.c_str());
	       if (E) {
		    if (!s || (line.compare(prevline) != 0 && line.compare("\n") != 0)) {
	           	printf("$\n");
		    }
		} else {
		    if (!s || (line.compare(prevline) != 0 && line.compare("\n") != 0)) {
	               printf("\n");
		    }
	        }
       prevline = line;
	}  	    
     }
}
