#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
 
/* since pipes are unidirectional, we need two pipes.
   one for data to flow from parent's stdout to child's
   stdin and the other for child's stdout to flow to
   parent's stdin */
 
#define NUM_PIPES          2
 
#define PARENT_WRITE_PIPE  0
#define PARENT_READ_PIPE   1
 
int pipes[NUM_PIPES][2];
 
/* always in a pipe[], pipe[0] is for read and 
   pipe[1] is for write */
#define READ_FD  0
#define WRITE_FD 1
 
#define PARENT_READ_FD  ( pipes[PARENT_READ_PIPE][READ_FD]   )
#define PARENT_WRITE_FD ( pipes[PARENT_WRITE_PIPE][WRITE_FD] )
 
#define CHILD_READ_FD   ( pipes[PARENT_WRITE_PIPE][READ_FD]  )
#define CHILD_WRITE_FD  ( pipes[PARENT_READ_PIPE][WRITE_FD]  )
using namespace std;
 
int
main()
{
    int outfd[2];
    int infd[2];
     
    // pipes for parent to write and read
    pipe(pipes[PARENT_READ_PIPE]);
    pipe(pipes[PARENT_WRITE_PIPE]);
     
    if(!fork()) {
        char *argv[]={"maxima", "-q", 0};
 
        dup2(CHILD_READ_FD, STDIN_FILENO);
        dup2(CHILD_WRITE_FD, STDOUT_FILENO);
 
        /* Close fds not required by child. Also, we don't
           want the exec'ed program to know these existed */
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
        close(PARENT_READ_FD);
        close(PARENT_WRITE_FD);
          
        execv(argv[0], argv);
    } else {
        char buffer[100];
        int count, bytes_read;
				string receive_output;
 
        /* close fds not required by parent */       
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
 
        // Write to childâs stdin
        write(PARENT_WRITE_FD, "display2d: false;\n", sizeof("display2d: false;\n"));
				sleep(1); 
				while (1)
        {
            bytes_read = read(PARENT_READ_FD, buffer, sizeof(buffer)-1);

            if (bytes_read <= 0)
                break;
            buffer[bytes_read] = '\0';
            receive_output += buffer;
        }
				while(1) {
				string input;
				cout << ">";
				cin >> input;
				write(PARENT_WRITE_FD, input.c_str(), sizeof(input.c_str()));
				while (1)
        {
            bytes_read = read(PARENT_READ_FD, buffer, sizeof(buffer)-1);

            if (bytes_read <= 0)
                break;

            buffer[bytes_read] = '\0';
            receive_output += buffer;
        }
        cout << receive_output << endl;
				}
    }
	return 0;
}
