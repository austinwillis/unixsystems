#include <stdlib.h>  
#include <stdio.h>  
#include <iostream>  
#include <sys/types.h>  
#include <sys/wait.h>  
#include <unistd.h>  
#include <fcntl.h> 

int main(){  
  const char* PROGRAM_NAME = "./child"; 
    char arg1[] = "arg1"; 
    char arg2[] = "arg2"; 
  char *args[] = { arg1, arg2, NULL };  

  int pipeForStdOut[2], pipeForStdIn[2];  
  std::string cntStdOut, cntStdIn;  

  char buf[32] = {0};  
  ssize_t bytesRead;  
  pid_t childPid;  

  pipe(pipeForStdOut);  
  pipe(pipeForStdIn);  

  childPid = fork();  
  if(childPid == -1){  
    perror("fork");  
    exit(-1);  
  }else if(childPid == 0){ 
        // remember 0 is for 1nput and 1 is for 0utput 
        close(pipeForStdOut[0]); // parent keeps the input 
        if(dup2(pipeForStdOut[1], 1) < 0) { // child gets the output end
            perror("dup2.1");  
            exit(-1);  
        }  

        close(pipeForStdIn[1]); // parent keeps the input 
        if(dup2(pipeForStdIn[0], 0) < 0){  
            perror("dup2.2");  
            exit(-1);  
        } 
	
	//char * const args[] = {NULL, "-r", "\"expand((x+1)^7);\"", "-q", NULL};
	char *const args[] =    {"/usr/bin/maxima", "-r", "expand((x+2)^6);", "-q", NULL};
	char * const envp[] = {NULL};
        std::cout << "executing child..." << std::endl;  
        if(execvp("/usr/bin/maxima", args) == -1){  
      std::cout << "failed to execute child process, exiting..." << std::endl; 
      perror("execve");  
      exit(-1);  
    }  
    exit(0);  
  }  
  wait(NULL);  

  std::cout << "tidying up..." << std::endl;  

    fcntl(pipeForStdOut[0], F_SETFL, O_NONBLOCK  | O_ASYNC);  
   while(1) { 
    bytesRead = read(pipeForStdOut[0], buf, sizeof(buf)-1); 
    if (bytesRead <= 0) break; 
    buf[bytesRead] = 0; // append null terminator 
    cntStdOut += buf; // append what wuz read to the string 
  }  
  std::cout << "<stdout>\n" << cntStdOut << "\n</stdout>" << std::endl; 

    fcntl(pipeForStdIn[0], F_SETFL, O_NONBLOCK  | O_ASYNC);  
   while(1) { 
    bytesRead = read(pipeForStdIn[1], buf, sizeof(buf)-1); 
    if (bytesRead <= 0) break; 
    buf[bytesRead] = 0; // append null terminator 
    cntStdIn += buf; // append what wuz read to the string 
  }  
  std::cout << "<stderr>\n" << cntStdIn << "\n</stderr>" << std::endl; 

  close(pipeForStdOut[0]);  
  close(pipeForStdIn[0]);  

  return 0;  
}  
