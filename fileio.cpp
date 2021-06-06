#include "fileio.h"


/** save
  * used to save the state of the tasks to a file
  * NOTE: doesn't deal with description or space names rn
  */
int save( const string& file, const vector<Task>& tasks ) {
    ofstream savefile { file };     // write out to this file
    if ( !savefile ) {
        return 1;                   // file couldn't be opened
    }

    /* write the tasks in plaintext to the file */
    for ( const Task& t : tasks ) {
        savefile << "Task " << t.getName() << " " << t.getPriority() << " {" << endl;
        
        savefile << "Tags {" << endl;
        for ( const string& s : t.getTags() ) {
            savefile << "  " << s << endl;
        }
        savefile << "  }" << endl;
        
        savefile << "}" << endl << endl;
    }

    return 0;
}

int load( const string& file, vector<Task>& tasks ) {
    ifstream readfile { file };     // get the file to read from
    if ( !readfile ) {
        return 1;                   // couldn't open the file
    }

    /* read in the tasks to add to the tasklist */
    string buffer;
    while ( getline(readfile, buffer, '{') ) {
        // make sure we didn't hit end
        if ( readfile.eof() ) 
            break;

        /* get the name and the priority */
        int priority;
        string name;
        stringstream ss { buffer };
                
        ss >> buffer >> name >> priority;               // read name, priority
        Task temp ( name, priority );                   // make new task

        /* get the rest */
        while ( readfile >> buffer ) {
            if ( buffer == "}" ) {
                break;
            }

            /* read in the tags */
            if ( buffer == "Tags" ) {
                readfile >> buffer >> buffer;   // twice for '{'
                while ( buffer != "}" ) {
                    temp.addTag( buffer );
                    readfile >> buffer;
                }
            }
        }

        /* add the newly created task to the list */
        tasks.push_back( temp );
    }

    return 0;
}
