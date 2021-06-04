# priority-list
A simple command line utility to make ranked to do lists with custom tags.

## File Structure

### main.cpp:
Used to implement the other methods and run the application loop.

### parse.h, parse.cpp:
Implements parsing of user commands and delegating tasks.
Also implements funcitons like adding, printing, removing, etc.

### task.h, task.cpp:
Implements the Task class to hold representation of a task for use.
Task:
  - name
  - description (not yet in use)
  - priority
  - tag list
