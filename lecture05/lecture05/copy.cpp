// File: getstat.cpp
// Program to display file status.
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <cstdlib>
using namespace std;

int checkargs(int argc, char *argv[]);
int getstat (const char *file, struct stat *sb);
void dispstat(char *file, const struct stat *sb);

int main(int argc, char *argv[])
{
   struct stat sb;

   checkargs(argc, argv);
   getstat(argv[1], &sb);
   dispstat(argv[1], &sb);

   return 0;
}  // end main

int checkargs(int argc, char *argv[])
{
   if (argc != 2) {
      cerr << "usage: " << argv[0] << " filename" << endl;
      exit(1);
   }

   return 0;
}  // end checkargs


int getstat (const char *file, struct stat *sb)
{
   if(lstat(file, sb) == -1) {
      cerr << "error: could not stat file" << endl;
      exit(2);
   }

   return 0;
}  // end getstat

void dispstat(char *file, const struct stat *sb)
{
   // Display file name
   cout << "File \"" << file << "\"" << endl;

   // Display file type 
   // File type is in the st_mode field along with perm info
   // Refer to the stat man page for these constants.
   switch (sb->st_mode & S_IFMT) {
      case S_IFREG:
         cout << "Ordinary file" << endl;
         break;
      case S_IFDIR:
         cout << "Directory" << endl;
         break;
      case S_IFLNK:
         cout << "Symbolic link" << endl;
         break;
      case S_IFIFO:
         cout << "FIFO" << endl;
         break;
      case S_IFSOCK:
         cout << "Socket" << endl;
         break;
      case S_IFCHR:
         cout << "Character special file" << endl;
         break;
      case S_IFBLK:
         cout << "Block special file" << endl;
         break;
      default:
         cout << "UNKNOWN TYPE" << endl;
   }  // end switch

   // Display owner id
   cout << "Owner ID: " << sb->st_uid << "; " ;

   // and name
   // Use getpwuid to parse the /etc/passwd file for us.
   // (See the man page.)
   struct passwd *pw;
   pw = getpwuid(sb->st_uid);
   cout << "Name: " << pw->pw_name << endl;
}  // end dispstat
