/*
Name: Stefan Suarez
Last Date Worked On: 11/15/15
Goal: Create a queue system that
functions using an elevator algorithm
and priority queues.
Status: DONE
*/

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include "PQ.h"

using namespace std;

/*
Function Name: Welcome
Purpose: Store the long welcome message so it doesn't clutter
up the main function.
*/
void Welcome() {
  cout << setfill('=') << setw(75) << "=" << endl;
  cout << "Welcome to Disc Scheduling." << endl;
  cout << "You may use the following commands:" << endl;
  cout << "1. EnqRequest <trackNumber>" << endl;
  cout << "2. ServeRequest" << endl;
  cout << "3. PrintState" << endl;
  cout << "4. Quit" << endl;
}

/*
Function Name: upCase
Purpose: Take care of case sensitivity issues in the program.
*/
void upCase(string& a1) {
  transform(a1.begin(), a1.end(), a1.begin(), (int (*)(int))toupper);
  return;
}

/*
Function Name: Quit
Purpose: Exit the program.
*/
void Quit(bool& endLoop) {
  cout << "Quit command received ... ";
  cout.flush();
  cout << "exiting." << endl;
  cout << setfill('=') << setw(75) << "=" << endl;
  endLoop = true;
}

/*
Function Name: printIndividualQueue
Purpose: Used like a visit function to
go through each item in the heap and print them out
in order of priority.
*/
void printIndividualQueue(pqClass q1) {
  bool endLoop = false;
  bool valuesRemain;
  pqItemType currentItem;
  int trackNumber, serialNumber;
  if (q1.PQueueIsEmpty()){
    cout << "(queue is empty)" << endl;
  } else {
    cout << "Track  Request Number" << endl;
    while(endLoop == false){
     //Since delete retrieves the first item in the queue
         //until there are none left, the loop deletes every
         //item in a copy of the queue and then outputs its
         //characteristics onto the console until there are
         //none left.
     q1.PQueueDelete(currentItem, valuesRemain);
     if(valuesRemain) {
       trackNumber = currentItem.GetTrackRequest();
       serialNumber = currentItem.GetSerialNum();
       cout << trackNumber;
       cout << setfill (' ') << setw(6) << " ";
       cout << serialNumber << endl;
     } else {
       endLoop = true;
     }
    } 
  }
}

/*
Function Name: PrintState
Purpose: Print out the current location and queue of the
program. Also print out the contents of both queues.
*/
void PrintState(pqClass cQueue, pqClass nQueue,
                int cTrack, string cDirection) {
  cout << "Current Position: .............. TRACK " << cTrack;
  cout << endl;
  cout << "Current Direction: ............. " << cDirection;
  cout << " DIRECTION" << endl;
  cout << "Current Queue: ................. " << cDirection;
  cout << " QUEUE" << endl;
  cout << endl;
  cout << "Contents of FORWARD QUEUE:" << endl;
  //If the current direction is forward, the current queue
    //is automatically the forward queue.
  if (cDirection == "FORWARD") {
    printIndividualQueue(cQueue);
    //Otherwise, the next queue is the forward queue.
  } else {
    printIndividualQueue(nQueue);
  }
  cout << endl;
  cout << "Contents of REVERSE QUEUE:" << endl;
  if (cDirection == "FORWARD") {
    printIndividualQueue(nQueue);
    //Otherwise, the next queue is the forward queue.
  } else {
    printIndividualQueue(cQueue);
  }
}

/*
Function Name: confirmReq
Purpose: Confirm that a request was processed
and notify the user what its number is as well
as the queue in which it was placed.
*/
void confirmReq(string cDirection, int cTrack,
                int requestNumber,
                string chosenQueue) {
  cout << "Current Position: .............. TRACK ";
  cout << cTrack << endl;
  cout << "Current Direction: ............. ";
  cout << cDirection << " DIRECTION" << endl;
  cout << "Request was Enqueued in the: ... ";
  cout << chosenQueue << " QUEUE" << endl;
  cout << "Number of Request is: .......... ";
  cout << requestNumber << endl;
}

/*
Function Name: QueueFull
Purpose: Store a message that will be printed
repeatedly by the enqrequest function in cases
where the desired queue is too full.
*/
void QueueFull () {
  cout << "Enqueue failed because there is not enough" << endl;
  cout << "room left in the necessary queue." << endl;
}

/*
Function Name: EnqRequest
Purpose: Enqueue requested tracks into a proper
priority queue following the elevator algorithm
Status: Works, but may need simplification.
*/
void EnqRequest(pqClass& cQueue, pqClass& nQueue,
                int cTrack, int trackRequest, 
                int& NextRequestSerial, 
                string cDirection) {
  //Vars
  pqItemType newItem;
  bool spaceLeft = true;
  newItem.SetTrackRequest(trackRequest);
  newItem.SetSerialNum(NextRequestSerial);
  //Multiple checks necessary
  //1. Check if requested track is the same as
    //the current track.
  if (cTrack == trackRequest) {
    //If so, automatically enque the request
       //in the next queue.
       //Provided the queue isn't full.
    //Also set the direction var for new item
       //according to the opposite direction
       //of cDirection.
    if(cDirection == "FORWARD") {
      newItem.SetMovingForward(false);
    } else {
      newItem.SetMovingForward(true);
    }
    nQueue.PQueueInsert(newItem, spaceLeft);
    if(spaceLeft) {
      //If current queue is forward, you inserted into
         //reverse.
      if(cDirection == "FORWARD") {
        confirmReq(cDirection, cTrack, NextRequestSerial,
             "REVERSE");
        ++NextRequestSerial;
      } else {
      //If the current queue is reverse, you inserted into
           //forward.
        confirmReq(cDirection, cTrack, NextRequestSerial,
             "FORWARD");
        ++NextRequestSerial;
      }
    } else {
      QueueFull();
    }
  } else {  
    //2. Check direction
    //If we are currently in the FORWARD QUEUE
    if (cDirection == "FORWARD") {
      //3. Compare current track to requested track.
      //And the requested track is ahead of the marker
      if(cTrack < trackRequest) {
        //Set direction to forward
        newItem.SetMovingForward(true);
        //Insert into the current queue.
        cQueue.PQueueInsert(newItem, spaceLeft);
        //If successful, confirm the request
        if(spaceLeft) {
          confirmReq(cDirection, cTrack, NextRequestSerial, "FORWARD");
          ++NextRequestSerial;
          //else
        } else {
          QueueFull();
        }
      //If the requested track is behind the marker, though,
      } else {
        //Set direction to reverse
        newItem.SetMovingForward(false);
        //Insert into the next queue
        nQueue.PQueueInsert(newItem, spaceLeft);
        //If successful, confirm request
        if(spaceLeft) {
          confirmReq(cDirection, cTrack, NextRequestSerial, "REVERSE");
          ++NextRequestSerial;
          //else
        } else {
          QueueFull();
        }
      }
    //If we are currently in the REVERSE QUEUE
    } else {
      //3. Compare current track to requested track.
      //And the requested track is behind of the marker
      if(cTrack > trackRequest) {
        //Set direction to reverse
        newItem.SetMovingForward(false);
        //Insert into the current queue.
        cQueue.PQueueInsert(newItem, spaceLeft);
        //If successful, confirm the request
        if(spaceLeft) {
          confirmReq(cDirection, cTrack, NextRequestSerial, "REVERSE");
          ++NextRequestSerial;
          //else
        } else {
          QueueFull();
        }
      //If the requested track is ahead of the marker, though,
      } else {
        //Set direction to forward
        newItem.SetMovingForward(true);
        //Insert into the next queue
        nQueue.PQueueInsert(newItem, spaceLeft);
        //If successful, confirm request
        if(spaceLeft) {
          confirmReq(cDirection, cTrack, NextRequestSerial, "FORWARD");
          ++NextRequestSerial;
          //else
        } else {
          QueueFull();
        }
      }
    }
  }
}

/*
Function Name: PrintServiceDetails
Purpose: Print out details of a service request
after one has been performed.
*/
void PrintServiceDetails(int pTrack, string pDirection, 
                         int trackNumber, int serialNumber, 
                         string cDirection, bool movingForward) {
  string reqQueue;
  //Interpret the bool value to a string for easier computation.
  if (movingForward == true){
    reqQueue = "FORWARD QUEUE";
  } else {
    reqQueue = "REVERSE QUEUE";
  }
  //Print out information
  cout << "Position Prior to Serve Operation: ... Track ";
  cout << pTrack << endl;
  cout << "Direction Prior to Serve Operation: .. ";
  cout << pDirection << " DIRECTION" << endl;
  cout << "The Request was Served from the: ..... ";
  cout << reqQueue << endl;
  cout << "Track Number of Request: ............. ";
  cout << trackNumber << endl;
  cout << "Number of Request: ................... ";
  cout << serialNumber << endl;
  cout << "Position After Serve Operation: ...... ";
  cout << "Track " << trackNumber << endl;
  cout << "Direction After Serve Operation: ..... ";
  cout << cDirection << " DIRECTION" << endl;
}
/*
Function Name: ServiceRequest
Purpose: Perform the next task in the current queue.
Status: Currently just a stub.
*/
void ServiceRequest(pqClass& cQueue, pqClass& nQueue,
                int& cTrack, string& cDirection) {
  bool success, movingForward;
  pqItemType currentItem;
  pqClass tempQueue;
  int trackNumber, serialNumber, pTrack;
  string pDirection;
  //Before doing anything, save the previous state.
  pTrack = cTrack;
  pDirection = cDirection;
  //Base case: Both queues are empty
  if(cQueue.PQueueIsEmpty() && nQueue.PQueueIsEmpty()) {
       cout << "No requests pending." << endl;
  //Normal Case 1: Current Queue is not empty
  } else if (!cQueue.PQueueIsEmpty()) {
    //valuesRemain will never be used in this set-up, because
    //the queue has to be empty for it to be triggered as false.
    //The if statements will automatically check for that.
    cQueue.PQueueDelete(currentItem, success);
    trackNumber = currentItem.GetTrackRequest();
    cTrack = trackNumber;
    serialNumber = currentItem.GetSerialNum();
    movingForward = currentItem.GetMovingForward();
    //Print data to the user to confirm the service.
    PrintServiceDetails(pTrack, pDirection, trackNumber,
       serialNumber, cDirection, movingForward);
  //Normal Case 2: Current Queue is empty but Next Queue isn't.
  } else if (cQueue.PQueueIsEmpty()) {
      //Switch your queues
      tempQueue = cQueue;
      cQueue = nQueue;
      nQueue = tempQueue;
      tempQueue.~pqClass();
      //Process the next request as normal
      cQueue.PQueueDelete(currentItem, success);
      trackNumber = currentItem.GetTrackRequest();
      cTrack = trackNumber;
      serialNumber = currentItem.GetSerialNum();
      movingForward = currentItem.GetMovingForward();
      //Also change the direction variable.
      if (cDirection == "FORWARD") {
        cDirection = "REVERSE";
      } else {
        cDirection = "FORWARD";
      }
      //Print data to the user to confirm the service.
      PrintServiceDetails(pTrack, pDirection, trackNumber,
       serialNumber, cDirection, movingForward);
  }
}

/*
Function Name: Main
Purpose: Create the main command loop
and necessary vars.
Notes for Future Development: You don't need
an array in this case, because the program has
its own protections against incorrect track numbers.
With a max string length of 12 for the command, you
can only enter a track number of 0 through 9 after
Enqrequest without tripping the if statement to false.
*/
int main() {
  //Define variables
  int CurrentTrack, NextRequestSerial, TrackRequest;
  string CurrentDirection, fullcommand, actualcommand;
  bool endMain = false;
  //Manipulater for string
    //Necessary for recognizing track number from command
    //when using EnqRequest command.
  istringstream ss;
  //PriorityQueues
    //Make sure to fix the classes because they are currently
    //not sufficient for your needs.
  pqClass CurrentQueue, NextQueue;
  //Initialize variables
  CurrentTrack = 0;
  NextRequestSerial = 0;
  CurrentDirection = "FORWARD";
  
  Welcome();

  while (endMain == false) {  
    cout << setfill('=') << setw(75) << "=" << endl;
    getline(cin, fullcommand);
    cout << endl;
    cout << fullcommand << endl;
    cout << endl;
    upCase(fullcommand);
    ss.str(fullcommand);
    //DO NOT REMOVE.
    //Clears the error flags which is necessary for the
    //stream to detect new input. Otherwise it simply rereads
    //the previous input.
    ss.clear();
    //Protection against artificially long commands
    if (fullcommand.length() < 13) {
      ss >> actualcommand;
      //Only use actual command to check for Enqrequest's parameter.
      //All others use the full command.
      if(actualcommand == "ENQREQUEST") {
        ss >> TrackRequest;
        //All possible tracks combined with enqrequest will
        //be exactly 12 characters long, so there is no need
        //for an if statement here to check for valid tracks.
        EnqRequest(CurrentQueue, NextQueue, CurrentTrack, 
                   TrackRequest, NextRequestSerial, 
                   CurrentDirection);
      } else if (fullcommand == "SERVEREQUEST") {
        ServiceRequest(CurrentQueue, NextQueue, CurrentTrack,
             CurrentDirection);
      } else if (fullcommand == "PRINTSTATE") {
        PrintState(CurrentQueue, NextQueue, CurrentTrack, 
                                    CurrentDirection);
      } else if (fullcommand == "QUIT") {
        Quit(endMain);
        //Destroy the queues.
        CurrentQueue.~pqClass();
        NextQueue.~pqClass();
      } else {
        //If no valid command was entered, do nothing.
      }
    } else {
      //If no valid command was entered, do nothing.
    }
  }

  return 0;
}