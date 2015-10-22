// This is an ls type program.  It displays entries in the current
// directory (by default) or in a directory passed as an argument.

#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <cstring>  // strerror()
#include <cstdlib>
using namespace std;

// Define error handling routines.
int errmsg(const char *str)
{
   cerr << str << endl;
   exit(1);
}

int uerrmsg(const char *str)
{
   cerr << str << ": " << strerror(errno) << endl;
   exit(errno);
}

int main(int argc, char *argv[])
{
   string dirname;

   if (argc == 1)
      dirname = ".";   // scan the current directory
   else if (argc == 2)
      dirname = argv[1];
   else
      errmsg("usage: dirscan [directory]");

   DIR *dp;
   // note that all unix routines expect a C char string not
   // a C++ string.  use c_str() to extract the C string.
   if((dp = opendir(dirname.c_str())) == NULL)
      uerrmsg("opendir");

   struct dirent *entry;
   while((entry = readdir(dp)) != NULL) {
      if(entry->d_name[0] != '.')    // check if file is hidden
         cout << entry->d_name << endl;
   }

   if(errno != 0)
      uerrmsg("readdir");

   return 0;
}
