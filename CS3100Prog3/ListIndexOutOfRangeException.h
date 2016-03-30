#ifndef my_LISTINDEXOUTOFRANGEEXCEPTION_H
#define my_LISTINDEXOUTOFRANGEEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class ListIndexOutOfRangeException: public out_of_range
{
   public:
      ListIndexOutOfRangeException(const string & message = "")
                    : out_of_range(message.c_str())
   { }
}; // end ListIndexOutOfRangeException

#endif
