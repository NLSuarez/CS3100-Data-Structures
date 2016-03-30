// *********************************************************
// Implementation file ListP.cpp for the ADT list.
// Pointer-based implementation.
// *********************************************************
#include <iostream>
#include "ListP.h" // header file
#include <cstddef> // for NULL
#include <cassert> // for assert()

bool check_ListP_code = false ;

List::List(): size(0), head(NULL)
{
} // end default constructor

List::List(const List& aList): size(aList.size), head(NULL)
{

  copyListNodes (aList) ;

} // end copy constructor

List::~List()
{
  removeAll ();

} // end destructor

bool List::isEmpty() const
{
   return bool(size == 0);
} // end isEmpty

int List::getLength() const
{
   return size;
} // end getLength

List::ListNode *List::find(int index) const
// --------------------------------------------------
// Locates a specified node in a linked list.
// Precondition: index is the number of the
// desired node.
// Postcondition: Returns a pointer to the desired
// node. If index < 1 or index > the number of
// nodes in the list, returns NULL.
// --------------------------------------------------
{
   if ( (index < 1) || (index > getLength()) )
      return NULL;

   else // count from the beginning of the list
   {  ListNode *cur = head;
      for (int skip = 1; skip < index; ++skip)
         cur = cur->next;
      return cur;
   } // end if
} // end find

void List::retrieve(int index,
                     ListItemType& dataItem) const
                       throw(ListIndexOutOfRangeException)
{
   if ((index < 1) || (index > getLength()))
      throw ListIndexOutOfRangeException(
      "ListOutOfRangeException: retrieve index out of range");
   else
   {  // get pointer to node, then data in node
      ListNode *cur = find(index);
      dataItem = cur->item;
   } // end if
} // end retrieve


void List::insert(int index, ListItemType newItem)
                    throw(ListIndexOutOfRangeException, ListException)
{
   int newLength = getLength() + 1;

   if ((index < 1) || (index > newLength))
      throw ListIndexOutOfRangeException(
      "ListOutOfRangeException: insert index out of range");
   else
   {  // create new node and place newItem in it
      ListNode *newPtr = new ListNode;
      if (newPtr == NULL)
         throw ListException(
         "ListException: insert cannot allocate memory");
      else
      {  size = newLength;
         newPtr->item = newItem;

         // attach new node to list
         if (index == 1)
         {  // insert new node at beginning of list
            newPtr->next = head;
            head = newPtr;
         }
         else
         {  ListNode *prev = find(index-1);
            // insert new node after node
            // to which prev points
            newPtr->next = prev->next;
            prev->next = newPtr;
         } // end if
      } // end if
   } // end if
} // end insert


void List::remove(int index)
                   throw(ListIndexOutOfRangeException)
{
   ListNode *cur;

   if ((index < 1) || (index > getLength()))
      throw ListIndexOutOfRangeException(
      "ListOutOfRangeException: remove index out of range");
   else
   {  --size;
      if (index == 1)
      {  // delete the first node from the list
         if (check_ListP_code) cout << "starting unlinking" << endl ;
         cur = head; // save pointer to node
         if (check_ListP_code) 
         {
           if (head==NULL) cout << "head is NULL" << endl ;
           else cout << "head is NOT NULL" << endl ;
         }

         head = head->next;
         if (check_ListP_code) cout << "finished unlinking" << endl ;
      }

      else
      {  ListNode *prev = find(index-1);
         // delete the node after the
         // node to which prev points
         cur = prev->next; // save pointer to node
         prev->next = cur->next;
      } // end if

      // return node to system
      if (check_ListP_code) cout << "starting deallocation" << endl ;
      cur->next = NULL;
      delete cur;
      cur = NULL;
      if (check_ListP_code) cout << "finishing deallocation" << endl ;
   } // end if
} // end remove

void List::copyListNodes (const List & aList)
                 throw(ListException)
{
  if (head != NULL)  
  {
     cout << "ListException: You may not copyListNodes to a non-empty list."
          << endl ;
     throw ListException
      ("ListException: You may not copyListNodes to a non-empty list.");
  }
  else /* TARGET IS EMPTY */
  {
     if (aList.head == NULL) head = NULL; // original list is empty
     else
     {  // copy first node
        head = new ListNode;
        assert(head != NULL); // check allocation
        head->item = aList.head->item;

          // copy rest of list
        ListNode *newPtr = head; // new list pointer
          // newPtr points to last node in new list
          // origPtr points to nodes in original list
        for (ListNode *origPtr = aList.head->next;
                       origPtr != NULL;
                       origPtr = origPtr->next)
        {  newPtr->next = new ListNode;
           assert(newPtr->next != NULL);
           newPtr = newPtr->next;
           newPtr->item = origPtr->item;
        } // end for

        newPtr->next = NULL;
     } // end if
  }  /* end else TARGET IS EMPTY */
} /* end function copyListNodes */

void List::removeAll ()
{
   if (check_ListP_code) cout << "List removeAll Starts" << endl ;
   while (!isEmpty())
   {
      if (check_ListP_code) cout << "list remove starting" << endl ;
      remove(1);
      if (check_ListP_code) cout << "list remove finished" << endl ;
   }
   if (check_ListP_code) cout << "List removeAll Finishes" << endl ;
}


List & List::operator=(const List& rhs)
{
      /* Check for assignment to self. */

   if (this != &rhs)
   {
     removeAll() ;
     copyListNodes(rhs);
     size = rhs.size ;
   }
   return *this ;
}
