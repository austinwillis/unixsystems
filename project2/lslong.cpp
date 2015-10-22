//Austin Willis
//Project 2
#include <pwd.h>
#include <ctime>
#include <time.h>
#include <algorithm>
#include <grp.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <vector>
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
    string dr = ".";
    DIR *dir;
    struct dirent *ent;
    int blocks = 0;
    //Get command line arguments
    if (argc > 2) {
	cerr << "Usage: lsl <directory>" << endl;
        exit(1);
    }
    if (argc == 2) {
	dr = argv[1];
    }   
    //Open directory and get total number of blocks
    if ((dir = opendir (dr.c_str())) != NULL) {
        getstat((dr.c_str()), &sb);
        while ((ent = readdir (dir)) != NULL) {
            if ((strcmp(ent->d_name ,(".")) != 0) && (strcmp(ent->d_name ,("..")) != 0)) {
 	        getstat(ent->d_name, &sb);
                blocks += sb.st_blocks/2;
            }
        }  
        cout << "Total: " << blocks << endl;
    }
    //Open directory and print each file's stat information
    if ((dir = opendir (dr.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
	    getstat(ent->d_name, &sb);
            if ((strcmp(ent->d_name ,(".")) != 0) && (strcmp(ent->d_name ,("..")) != 0))
		dispstat(ent->d_name, &sb);
  	}
  	closedir (dir);
    } else {
  	perror ("");
  	return EXIT_FAILURE;
    }	
    return 0;
}

//Open all files in a directory
vector <string> readdir( const string& path = string() ) {
    vector <string> result;
    dirent* de;
    DIR* dp;
    errno = 0;
    dp = opendir( path.empty() ? "." : path.c_str() );
    if (dp) {
    	while (true) {
      	    errno = 0;
      	    de = readdir( dp );
      	    if (de == NULL) break;
      	    	result.push_back( string( de->d_name ) );
      	}
    	closedir( dp );
    }
    sort( result.begin(), result.end() );
    return result;
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
    switch (sb->st_mode & S_IFMT) {
        case S_IFREG:
            permstr = '-';
            break;
      	case S_IFDIR:
            permstr = 'd';
            break;
     	 case S_IFLNK:
            permstr = 'l';
            break;
      	case S_IFIFO:
            permstr = 'p';
            break;
      	case S_IFSOCK:
            permstr = 's';
            break;
      	case S_IFCHR:
            permstr = 'c';
            break;
      	case S_IFBLK:
            permstr = 'b';
            break;
    }

    struct passwd *pw;
    pw = getpwuid(sb->st_uid);
    struct group *gr;
    gr = getgrgid(sb->st_gid);
    int perms = sb->st_mode & (S_IRWXU|S_IRWXG|S_IRWXO);
    if (perms & S_IRUSR) permstr += 'r'; else permstr += '-';
    if (perms & S_IWUSR) permstr += 'w'; else permstr += '-';
    if (perms & S_IXUSR) permstr += 'x'; else permstr += '-';
    if (perms & S_IRGRP) permstr += 'r'; else permstr += '-';
    if (perms & S_IWGRP) permstr += 'w'; else permstr += '-';
    if (perms & S_IXGRP) permstr += 'x'; else permstr += '-';
    if (perms & S_IROTH) permstr += 'r'; else permstr += '-';
    if (perms & S_IWOTH) permstr += 'w'; else permstr += '-';
    if (perms & S_IXOTH) permstr += 'x'; else permstr += '-';
    cout << permstr << " ";
    cout << sb->st_nlink << " ";
    cout << pw->pw_name << " ";
    cout << gr->gr_name << " ";
    cout << right << setw(5) << sb->st_size << " ";
    char buff[100];
    time_t filet = sb->st_atime;
    strftime (buff, 100, "%b %d %H:%M", localtime (&filet));
    printf ("%s ", buff);
    cout << file << endl;
    return;
}
