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
int parseCommand( const string& cmd, vector<Task>& tasks, string& file ) {
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
    else if ( arg == "tag" || arg == "t" ) {
        addTags( ss, tasks );
    }
    else if ( arg == "untag" || arg == "u" ) {
        removeTags( ss, tasks );
    }
    else if ( arg == "file" || arg == "f" ) {
        ss >> file;
    }
    else if ( arg == "save" || arg == "s" ) {
        save( file, tasks );
    }
    else if ( arg == "load" || arg == "l" ) {
        load( file, tasks );
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
    // get the first tag
    string tag = "";
    ss >> tag;
    
    // check if any tags requested
    if ( tag.size() == 0 ) {
        ss.clear();             // reset the stream
        ss.str("all");
        showTasks( ss, tasks );
        return;
    }
    
    // if we have tags, make a priority queue
    priority_queue<Task> tasklist;
    unordered_set<string> names;        // keeps the tasks we've added

    do {
        // search for items with this tag
        for ( const Task& t : tasks ) {
            if ( t.hasTag(tag) && (names.count(t.getName()) == 0) ) {
                if ( t.active() || tag == "finished" ) {
                    tasklist.push(t);
                    names.insert( t.getName() );
                }
            }
        }
    } while ( ss >> tag );

    // print out the priority queue
    cout << "Tasks: " << endl;
    while ( !(tasklist.empty()) ) {
        Task t = tasklist.top();        // get the element
        
        cout << "  " << t.getName() << " - " << t.getPriority() << " : ";
        for ( const string& tag : t.getTags() ) {
            if ( !hiddenTag(tag) )
                cout << tag << ", ";
        }
        cout << endl;

        tasklist.pop();     // remove the element
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


void addTags( stringstream& ss, vector<Task>& tasks ) {
    string name, tag;
    ss >> name;

    vector<Task>::iterator modtask;
    for ( modtask = tasks.begin(); modtask != tasks.end(); ++modtask ) {
        if ( modtask->getName() == name ) {
            break;
        }
    }
    if ( modtask == tasks.end() ) return;

    while ( ss >> tag ) {
        modtask->addTag( tag );
    }

    return;
}

void removeTags( stringstream& ss, vector<Task>& tasks ) {
    string name, tag;
    ss >> name;
    
    vector<Task>::iterator modtask;
    for ( modtask = tasks.begin(); modtask != tasks.end(); ++modtask ) {
        if ( modtask->getName() == name ) {
            break;
        }
    }
    if ( modtask == tasks.end() ) return;

    while ( ss >> tag ) {
        modtask->removeTag( tag );
    }

    return;
}


bool hiddenTag( const string& tag ) {
    if ( tag == "all" ) {
        return true;
    } else if ( tag == "finished" ) {
        return true;
    } else {
        return false;
    }
}
