// File: getstat.cpp
// Program to display file status.
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime>
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
   string perm;
   // Display file type 
   // File type is in the st_mode field along with perm info
   // Refer to the stat man page for these constants.
   switch (sb->st_mode & S_IFMT) {
      case S_IFREG:
         cout << "Ordinary file" << endl;
	 perm = perm + '-';
         break;
      case S_IFDIR:
         cout << "Directory" << endl;
	 perm = perm + 'd';
         break;
      case S_IFLNK:
         cout << "Symbolic link" << endl;
	 perm = perm + 'l';
         break;
      case S_IFIFO:
         cout << "FIFO" << endl;
	 perm = perm + 'p';
         break;
      case S_IFSOCK:
         cout << "Socket" << endl;
	 perm = perm + 's';
         break;
      case S_IFCHR:
         cout << "Character special file" << endl;
	 perm = perm + 'c';
         break;
      case S_IFBLK:
         cout << "Block special file" << endl;
	 perm = perm + 'b';
         break;
      default:
         cout << "UNKNOWN TYPE" << endl;
	 perm = perm + 'u';
   }  // end switch

   // Display owner id
   cout << "Owner ID: " << sb->st_uid << "; " ;

   // and name
   // Use getpwuid to parse the /etc/passwd file for us.
   // (See the man page.)
   struct passwd *pw;
   pw = getpwuid(sb->st_uid);
   cout << "Name: " << pw->pw_name << endl;

   cout << "Inode number: " << sb->st_ino << endl;
   cout << "# of hard links: " << sb->st_nlink << endl;
   cout << "File size: " << sb->st_size << endl;

   cout << "Permissions (octal): ";

   // Owner permissions
   cout << ((sb->st_mode & S_IRWXU) >> 6);
   if (sb->st_mode & S_IRUSR)
      perm = perm + 'r';
   else
      perm = perm + '-';
   if (sb->st_mode & S_IWUSR)
      perm = perm + 'w';
   else
      perm = perm + '-';
   if (sb->st_mode & S_IXUSR)
      perm = perm + 'x';
   else
      perm = perm + '-';
   // Group permissions
   cout << ((sb->st_mode & S_IRWXG) >> 3);
   if (sb->st_mode & S_IRGRP)
      perm = perm + 'r';
   else
      perm = perm + '-';
   if (sb->st_mode & S_IWGRP)
      perm = perm + 'w';
   else
      perm = perm + '-';
   if (sb->st_mode & S_IXGRP)
      perm = perm + 'x';
   else
      perm = perm + '-';
   cout << endl << "Permissions (symbolic): " << perm << endl;

   // Access time
   struct tm *bt = localtime(&sb->st_atime);
   cout << setfill('0');
   cout << "Access: " << bt->tm_year+1900 << '-' << setw(2) << bt->tm_mon << '-' << setw(2) << bt->tm_mday << endl;
   
   
}  // end dispstat
