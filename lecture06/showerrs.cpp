#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>  // perror()
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
   if(argc != 2) 
      { cerr << "usage: showerrs filename" <<  endl; exit(1); }

   int fd;
   if((fd = open(argv[1], O_RDWR)) == -1) 
      { perror("showerrs"); exit(2); }

   if(close(fd) == -1) 
      { perror("showerrs"); exit(2); }
   return 0;
}
