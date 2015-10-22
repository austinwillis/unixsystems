//Austin Willis
//Project 2, count-opens

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main(int argc, char **argv) {
    int i = 3;
    ofstream *f;
    do {
	// Open a file
        f = new ofstream( to_string(i++) );
    } while ( * f << "hello" << flush );
      // Try to output to file
    -- i;
    //Don't count failed open
    std::cout << i << '\n';
}

//Opens 1024 files
