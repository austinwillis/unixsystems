// File: bytcat.cpp
// byte at a time cat from stdin using system calls

#include <unistd.h>

int main()
{
   char c;
   ssize_t nread, nwrite;

   while ((nread = read(0, &c, sizeof(c))) != -1) {
      if (nread == 0)
         break;	// break on end-of-file
      if((nwrite = write(1, &c, nread)) == -1)
         break;  // break on write error
   }  // end while

   if (nread == -1 || nwrite == -1)
      return 1;  // error occurred

   return 0;
}  // end main
