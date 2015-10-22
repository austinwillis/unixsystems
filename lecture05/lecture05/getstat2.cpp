// Program to display file status.
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <cstdlib>
#include <iomanip>
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
}

int checkargs(int argc, char *argv[])
{
   if (argc != 2) {
      cerr << "usage: " << argv[0] << " filename" << endl;
      exit(1);
   }

   return 0;
}


int getstat (const char *file, struct stat *sb)
{
   if(lstat(file, sb) == -1) {
      cerr << "error: could not stat file" << endl;
      exit(2);
   }

   return 0;
}

void dispstat(char *file, const struct stat *sb)
{
   string permstr;

   // Display file name
   cout << "File \"" << file << "\"" << endl;

   // Display file type 
   // File type is in the st_mode field along with perm info
   // Refer to the stat man page for these constants.
   switch (sb->st_mode & S_IFMT) {
      case S_IFREG:
         permstr = '-';
         cout << "Ordinary file" << endl;
         break;
      case S_IFDIR:
         permstr = 'd';
         cout << "Directory" << endl;
         break;
      case S_IFLNK:
         permstr = 'l';
         cout << "Symbolic link" << endl;
         break;
      case S_IFIFO:
         permstr = 'p';
         cout << "FIFO" << endl;
         break;
      case S_IFSOCK:
         cout << "Socket" << endl;
         permstr = 's';
         break;
      case S_IFCHR:
         permstr = 'c';
         cout << "Character special file" << endl;
         break;
      case S_IFBLK:
         permstr = 'b';
         cout << "Block special file" << endl;
         break;
      default:
         cout << "UNKNOWN TYPE" << endl;
   }

   // Display owner id
   cout << "Owner ID: " << sb->st_uid << "; " ;
   // and name
   // Use getpwuid to parse the /etc/passwd file for us.
   // (See the man page.)
   struct passwd *pw;
   pw = getpwuid(sb->st_uid);
   cout << "Name: " << pw->pw_name;
   cout << "      ";

   // Display group id
   cout << "Group ID: " << sb->st_gid << "; " ;
   // and name
   // Use getgrgid to parse the /etc/group file for us.
   // (See the man page.)
   struct group *gr;
   gr = getgrgid(sb->st_gid);
   cout << "Name: " << gr->gr_name;
   cout << endl;


   cout << "inode: " << sb->st_ino;
   cout << "     hard links: " << sb->st_nlink;
   cout << "     size: " << sb->st_size;
   cout << endl;
   int perms = sb->st_mode & (S_IRWXU|S_IRWXG|S_IRWXO);
   cout << "permissions: " << oct << perms << dec;
   if (perms & S_IRUSR) permstr += 'r'; else permstr += '-';
   if (perms & S_IWUSR) permstr += 'w'; else permstr += '-';
   if (perms & S_IXUSR) permstr += 'x'; else permstr += '-';
   if (perms & S_IRGRP) permstr += 'r'; else permstr += '-';
   if (perms & S_IWGRP) permstr += 'w'; else permstr += '-';
   if (perms & S_IXGRP) permstr += 'x'; else permstr += '-';
   if (perms & S_IROTH) permstr += 'r'; else permstr += '-';
   if (perms & S_IWOTH) permstr += 'w'; else permstr += '-';
   if (perms & S_IXOTH) permstr += 'x'; else permstr += '-';
   cout << " (" << permstr << ")" << endl;
   return;
}

