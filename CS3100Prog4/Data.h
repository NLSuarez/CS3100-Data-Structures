#ifndef my_DATA_H
#define my_DATA_H

class itemClass
{
/*  ==================================================

  ================================================== */
  private:

    int trackRequest ;
    int serialNum ;
    //Since we can only go either forward or backward,
    //a bool var will suffice.
    //IMPORTANT NOTE: This field will be set to TRUE
    //when we are dealing with a forward moving queue.
    //Otherwise, it will be set to FALSE for a reverse
    //queue.
    bool movingForward ;


  public:

/*  ==================================================
                 Default constructor
  ================================================== */
    itemClass() ;

/* Prototypes for methods you might want to implement 
   - add to what's here in whatever way you find useful */
   
/*  ==================================================
                    Constructor
  ================================================== */
    itemClass(int trackRequest, int serialNum, bool movingForward) ;

/*  ==================================================
                  GetTrackRequest
  ================================================== */
    int GetTrackRequest() const ;     

/*  ==================================================
                  GetSerialNum
  ================================================== */
    int GetSerialNum() const ;

/*  ==================================================
                  GetMovingForward
  ================================================== */
    bool GetMovingForward() const;

/*  ==================================================
                  SetTrackRequest
  ================================================== */
    void SetTrackRequest(int req) ;     

/*  ==================================================
                  SetSerialNum
  ================================================== */
    void SetSerialNum(int num) ; 
/*  ==================================================
                  SetMovingForward
  ================================================== */
    void SetMovingForward(bool movingForward) ;

/*  ==================================================
                       Key
  ================================================== */
/* This method returns the search key.  
   Here we assume that the key is the item itself,
   but you can change that if you want. */

    itemClass Key() const ;

/*  ==================================================
                       Equality Test 
  ================================================== */
bool operator== (const itemClass& Rhs) const ;

/*  ==================================================
                     non-Equality Test 
  ================================================== */
bool operator!= (const itemClass& Rhs) const ;

/*  ==================================================
                     Less-Than Test 
  ================================================== */
bool operator< (const itemClass& Rhs) const ;

/*  ==================================================
                  Less-Than-Or-Equal Test 
  ================================================== */
bool operator<= (const itemClass& Rhs) const ;

/*  ==================================================
                   Greater-Than Test 
  ================================================== */
bool operator> (const itemClass& Rhs) const ;

/*  ==================================================
               Greater-Than-Or-Equal Test 
  ================================================== */
bool operator>= (const itemClass& Rhs) const ;


} ;  // end class

#endif
