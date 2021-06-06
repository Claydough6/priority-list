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
