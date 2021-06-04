/* parse.h: utilities for parsing inputs */

#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <queue>

#include "task.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::priority_queue;

void printHelp();

int parseCommand( const string& cmd, vector<Task>& tasks );

void addTask( stringstream& ss, vector<Task>& tasks );

void removeTask( stringstream& ss, vector<Task>& tasks );

void showBasic( const vector<Task>& tasks );

void showTasks( stringstream& ss, const vector<Task>& tasks );

void addTags( stringstream& ss, vector<Task>& tasks );

void removeTags( stringstream& ss, vector<Task>& tasks );

bool hiddenTag( const string& tag );

#endif
