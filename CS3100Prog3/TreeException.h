#ifndef my_TREEEXCEPTION_H
#define my_TREEEXCEPTION_H

// ********************************************************
// Header file TreeException.h for the ADT binary tree.
// ********************************************************
#include <stdexcept>
#include <string>

using namespace std;

class TreeException : public runtime_error
{
public:
   TreeException(const string & message =""):
      runtime_error(message.c_str()) { }
}; // end TreeException

#endif
