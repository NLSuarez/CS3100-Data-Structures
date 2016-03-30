#ifndef my_LISTEXCEPTION_H 
#define my_LISTEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class ListException: public runtime_error
{
   public:
      ListException(const string & message = "")
           : runtime_error(message.c_str())
   { }
}; // end ListException

#endif
