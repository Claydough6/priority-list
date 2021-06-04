/* main.cpp: the main file to run priority-list code 
 *   deals mostly with input and output and parsing
 */

#include <iostream>
#include <string>
#include <sstream>

#include "task.h"
#include "parse.h"

using std::cout;
using std::cin;
using std::endl;

using std::string;
using std::stringstream;
using std::getline;




/** main
  * runs the app
  */
int main( int argc, char** argv ) {
    /* check which mode the user started */
    bool arg_mode = true;           // puts the program into default argument mode
    if ( argc == 1 )
        arg_mode = false;           // puts the program into command mode
    
    // feature not implemented yet
    if ( arg_mode )
        return EXIT_FAILURE;

    /* make the structure to hold the tasks */
    vector<Task> tasks;

    /* loop and look at input, parsing it */
    string cmd;
    cout << "> ";
    while ( getline(cin, cmd) ) {
        int rval = parseCommand( cmd, tasks );     // parse the command
            
        if ( rval == 1 )
            break;
        if ( rval != 0 )
            return EXIT_FAILURE;

        cout << "> ";
    }

    return EXIT_SUCCESS;
}
