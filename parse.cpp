/* parse.cpp: utilities for parsing input (outlined in parse.h) */

#include "parse.h"

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
  * Input: a string argument for the command issued, a reference to the task list
  * Output: 0 if success, other if failure (error code)
  *     0 -- success
  *     1 -- quit
  *     2 -- other error
  * parses the command and delegates task to other functions
  */
int parseCommand( const string& cmd, vector<Task>& tasks ) {
    string arg;
    stringstream ss {cmd};
    ss >> arg;

    /* just check to see if it's in a the list of valid args */
    if ( arg == "help" || arg == "h" ) {
        getHelp();
    }
    else if ( arg == "quit" || arg == "q" ) {
        return 1;
    }
    else if ( arg == "add" || arg == "a" ) {
        addTask( ss, tasks );
    }
    else if ( arg == "show" || arg == "print" || arg == "s" || arg == "p" ) {
        showTasks( ss, tasks );
    }
    else if ( arg == "remove" || arg == "r" ) {
        removeTask( ss, tasks );
    }

    return 0;
}


void addTask( stringstream& ss, vector<Task>& tasks ) {
    string name, next;
    int priority;

    ss >> name >> next;         // fetch name and first arg
        
    // figure out the priority
    try {
        priority = stoi(next);      // convert to priority
        if ( !(ss >> next) )          // fetch the next string
            next = "";
    } catch( ... ) {
        priority = 9;
    }

    Task t ( name, priority );  // make the task object
        
    // read in the tags        
    do {
        if ( next.size() ) 
            t.addTag(next);
    } while ( ss >> next );

    // add the task to the task list if not there
    bool in = false;
    for ( const Task& task : tasks ) {
        if ( task.getName() == t.getName() )
            in = true;
    }
    if ( !in )
        tasks.push_back(t);
}


void showTasks( stringstream& ss, const vector<Task>& tasks ) {
    for ( const Task& t : tasks ) {
        cout << t.getName() << " - " << t.getPriority() << " : ";
        for ( const string& s : t.getTags() ) {
            if ( s != "all" )
                cout << s << " ";
        }
        cout << endl;
    }
}


void removeTask( stringstream& ss, vector<Task>& tasks ) {
    string name;
    ss >> name;

    vector<Task>::iterator iter;
    for ( iter = tasks.begin(); iter != tasks.end(); ++iter ) {
        if ( iter->getName() == name ) {
            tasks.erase(iter);
            break;
        }
    }
}