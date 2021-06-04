/* main.cpp: the main file to run priority-list code 
 *   deals mostly with input and output and parsing
 */

#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;

using std::string;
using std::stringstream;
using std::getline;


/** getHelp
  * prints out usage for the app to the user
  */
void getHelp() {
    cout << "pritority-list: quick CLI to-do list utility" << endl;
    cout << endl;
    cout << "\tDescription..." << endl;
    cout << endl;
    cout << "Usage: priority-list [args] ... " << endl;    
}

/** parseCommand
  * Input: a string argument for the command issued
  * Output: 0 if success, other if failure (error code)
  *     0 -- success
  *     1 -- quit
  *     2 -- other error
  * parses the command and delegates task to other functions
  */
int parseCommand( const string& cmd ) {
    string arg;
    stringstream ss {cmd};
    ss >> arg;

    /* just check to see if it's in a the list of valid args */
    if ( arg == "help" || arg == "h" ) {
        getHelp();
        return 0;
    }
    else if ( arg == "quit" || arg == "q" ) {
        return 1;
    }
    else if ( arg == "add" || arg == "a" ) {
        cout << "would add..." << endl; 
    }
    else if ( arg == "show" || arg == "print" || arg == "s" || arg == "p" ) {
        cout << "would display stuff..." << endl;
    }

    return 0;
}

/** main
  * runs the app
  */
int main( int argc, char** argv ) {
    /* check which mode the user started */
    bool arg_mode = true;           // puts the program into default argument mode
    if ( argc == 1 )
        arg_mode = false;           // puts the program into command mode

    /* parse the arguments and do the tasks given */
    if ( arg_mode ) {
        /* verify the arguments (if argument mode) */
    } else {
        /* loop and look at input, parsing it */
        string cmd;
        cout << "> ";
        while ( getline(cin, cmd) ) {
            int rval = parseCommand( cmd );     // parse the command
            
            if ( rval == 1 )
                break;
            if ( rval != 0 )
                return EXIT_FAILURE;

            cout << "> ";
        }
    }

    return EXIT_SUCCESS;
}
