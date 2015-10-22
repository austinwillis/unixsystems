// File: getopt.cpp
// Example program demonstrating use of getopt()
// The program accepts afl and w options.
// Options f and w require an additional argument

#include <unistd.h>  // getopt(), externally defined: opterr, optarg, optind
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    int opt, warg;
    bool opt_a = false;
    bool opt_f = false;
    bool opt_l = false;
    bool opt_w = false;
    string farg;

    // setting opterr to 0 suppresses the default error message.
    opterr = 0;

    // Process comand-line options
    // The program accepts afl and w options.
    // Options f and w require an additional argument
    while((opt = getopt(argc, argv, "af:lw:")) != -1) {
        switch(opt) {
        case 'a':
            opt_a = true;
            cout << "option: " << static_cast<char>(opt) << "\n";
            break;
        case 'f':
            opt_f = true;
            // f option requires a string argument.
            farg = optarg;
            cout << "option: " << static_cast<char>(opt) << " with argument "
                 << farg << "\n";
            break;
        case 'l':
            opt_l = true;
            cout << "option: " << static_cast<char>(opt) << "\n";
            break;
        case 'w':
            opt_w = true;
            // w option requires a numeric argument.
            warg = atoi(optarg);
            cout << "option: " << static_cast<char>(opt) << " with argument "
                 << warg << "\n";
            break;
        case '?':
            cout << "unknown option: " << static_cast<char>(optopt) << "\n";
            break;
        }
    }

    // Anything left is an argument (not an option)
    // getopt rearranges argv[] so that arguments are at end
    // optind starts at the first non-option argument
    for(; optind < argc; optind++) {
        cout << "argument: " << argv[optind] << "\n";
    }

    return 0;
}
