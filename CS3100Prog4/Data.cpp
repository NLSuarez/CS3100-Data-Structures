#include<iostream>
#include "Data.h"

/* Put in definitions of methods declared in Data.h 
   - modify as you wish. */

/*  ==================================================
                 Default constructor
  ================================================== */
itemClass::itemClass() : trackRequest(-100), 
                         serialNum(-1)
{
}

/*  ==================================================
                    Constructor
  ================================================== */
itemClass::itemClass(int trkR, int srlNum, bool movingForward) 
       : trackRequest(trkR),
         serialNum (srlNum),
         movingForward(movingForward)
{
}

/*  ==================================================
                  GetTrackRequest
  ================================================== */
int itemClass::GetTrackRequest() const
{
  return trackRequest ;
}

/*  ==================================================
                  GetSerialNum
  ================================================== */
int itemClass::GetSerialNum() const 
{
  return serialNum ;
}
/*  ==================================================
                  GetMovingForward
  ================================================== */

bool itemClass::GetMovingForward() const
{
  return movingForward ;
}

/*  ==================================================
                  SetTrackRequest
  ================================================== */
void itemClass::SetTrackRequest(int req)
{
  trackRequest = req ;
}

/*  ==================================================
                  SetSerialNum
  ================================================== */
void itemClass::SetSerialNum(int num)
{
  serialNum = num ;
}

/*  ==================================================
                  SetMovingForward
  ================================================== */
void itemClass::SetMovingForward(bool direction)
{
  //If moving in a forward direction, moving forward is
  //true.
  movingForward = direction;
}

/*  ==================================================
                       Key
  ================================================== */
/* This method returns the search key.  
   Here we assume the key is the item itself. */

itemClass itemClass::Key() const
{
  return *this ;
}

/*  ==================================================
                       Equality Test 
  ================================================== */
bool itemClass::operator== (const itemClass& Rhs) const
{
  return (trackRequest == Rhs.trackRequest) 
            && (serialNum == Rhs.serialNum) ;
}

/*  ==================================================
                     non-Equality Test 
  ================================================== */
bool itemClass::operator!= (const itemClass& Rhs) const
{
  return !(*this==Rhs) ;
}

/*  ==================================================
                     Less-Than Test 
  ================================================== */
bool itemClass::operator< (const itemClass& Rhs) const
{
   if(movingForward == true) {
     //Forward Queue Possibilities
     //Track Numbers Equal But Serial Numbers Different
     if (trackRequest == Rhs.trackRequest
        && serialNum > Rhs.serialNum) {
        return true;
        //Track Numbers and Serial Numbers Different
     } else if (trackRequest > Rhs.trackRequest) {
       return true;
     } else {
       return false;
     }
   } else {
     //Reverse Queue Possibilities
     //Track Numbers Equal But Serial Numbers Different
     if (trackRequest == Rhs.trackRequest
        && serialNum > Rhs.serialNum) {
        return true;
        //Track Numbers and Serial Numbers Different
     } else if (trackRequest < Rhs.trackRequest) {
        return true;
     } else {
        return false;
     }
   }
}

/*  ==================================================
                  Less-Than-Or-Equal Test 
  ================================================== */
bool itemClass::operator<= (const itemClass& Rhs) const
{
  return (*this<Rhs) || (*this==Rhs) ;
}

/*  ==================================================
                   Greater-Than Test 
  ================================================== */
bool itemClass::operator> (const itemClass& Rhs) const
{
  return (!(*this<Rhs) && !(*this==Rhs)) ;
  /* OR return (Rhs<*this); */
}

/*  ==================================================
               Greater-Than-Or-Equal Test 
  ================================================== */
bool itemClass::operator>= (const itemClass& Rhs) const
{
  return ( !(*this<Rhs) ) ;  
}

/*  ==================================================
  ================================================== */

/*  ==================================================
  ================================================== */
