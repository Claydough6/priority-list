#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "task.h"

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::cout;

int save( const string& file, const vector<Task>& tasks );

int load( const string& file, vector<Task>& tasks );

#endif
