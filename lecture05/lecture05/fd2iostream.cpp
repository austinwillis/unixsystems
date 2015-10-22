// cat-like program that reads from input file that is passed
// as first program argument and writes to standard output.

// The program demonstrates mapping a UNIX file descriptor to
// an iostream.

// You will need to install the boost libraries.

// To compile under Linux:
// g++ -o fd2iostream fd2iostream.cpp -lboost_iostreams

// To compile under Cygwin:
// g++ -o fd2iostream fd2iostream.cpp
//           -I /usr/include/boost-1_33_1 -lboost_iostreams-gcc-mt-s

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <iostream>
#include <boost/iostreams/stream.hpp> 
#include <boost/iostreams/device/file_descriptor.hpp> 

using namespace std;
using namespace boost::iostreams;

int main(int argc, char *argv[])
{
   int fd;
   string str;
   if(argc != 2) {
      cerr << "error: fd2iostream infile" << endl;
      return 1;
   }

   // Associate UNIX fd with file argument
   if((fd = open(argv[1], O_RDONLY)) == -1) {
      perror(argv[0]); 
      return 2;
   }

   // Associate stream "in" with fd file descriptor
   stream<file_descriptor> in(fd);

   // Associate stream "out" with standard output file descriptor
   stream<file_descriptor> out(2);

   // Now read from stream "in" and write to stream "out".
   while(in) {
      getline(in, str);
      out << str << endl;
   }

   return 0;
}
