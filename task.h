#ifndef TASK_H
#define TASK_H

#include <vector>
#include <string>
#include <unordered_set>

using std::vector;
using std::string;
using std::unordered_set;


class Task {
private:
    string name;                    // name of the task
    string description;             // optional task description

    int priority;                   // used to keep track of priority of task
    
    unordered_set<string> tags;     // holds all of the tasks tags

public:
    // constructors
    Task( const string& name );
    Task( const string& name, int priority );
    
    // getters
    int getPriority() const;
    const string& getName() const;
    const string& getDesc() const;
    const unordered_set<string>& getTags() const;

    // setters
    void setPriority( int p );
    void setDesc( const string& desc );
    void addTag( const string& tag );
    void removeTag( const string& tag );

    // useful
    bool hasTag( const string& tag ) const;
    bool operator< ( const Task& other ) const;
    bool active() const;
};

#endif
