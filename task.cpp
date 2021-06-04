/* task.cpp: implementation for task class in task.h */

#include "task.h"

/* constructors */
Task::Task( const string& name ) {
    this->name = name;
    
    priority = 9;
    description = "";
    tags.insert("all");
}

Task::Task( const string& name, int priority ) {
    this->name = name;
    this->priority = 9;
    
    if ( priority >= 0 && priority < 10 )
        this->priority = priority;

    description = "";
    tags.insert("all");
}

/* getters */
int Task::getPriority() const {
    return priority;
}

const string& Task::getName() const {
    return name;
}

const string& Task::getDesc() const {
    return description;
}

const unordered_set<string>& Task::getTags() const {
    return tags;
}

/* setters */
void Task::setPriority( int p ) {
    // make sure 0 <= p <= 9 for priority values
    if ( p < 0 || p > 9 )
        return;

    priority = p;
}

void Task::setDesc( const string& desc ) {
    description = desc;
}

void Task::addTag( const string& tag ) {
   tags.insert( tag );
}

void Task::removeTag( const string& tag ) {
    tags.erase( tag );
}

/* various useful functions */
bool Task::hasTag( const string& tag ) const {
    return ( tags.count(tag) > 0 );
}
