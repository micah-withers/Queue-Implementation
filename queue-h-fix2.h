// File: Queue_T.h
//
// Author: Micah Withers
// Course: CIS-221
// Assignment: Queue implementation using a dynamic circular array
//
//I typed all of this code on my own, I did not show my code
//      to anyone, I did not look at anyone else's code, and no
//      code was copied.
//
// Purpose: Header file for templatized queue class.
// This class is being constructed to provide more flexibility
// (over an array) in the data structures we want.
// This file includes definitions for a Queue and Link_Node.
//
// Value Semantics: Assignment and copy constructor may be used with Queue.

#ifndef QUEUE_T_H
#define QUEUE_T_H

// This header defines "size_t"
#include <cstdlib>

#include <stdexcept>

/*****************************************************************************
 * class: Queue
 * desc: Defines a generic "first-in/first-out" (FIFO) Abstract Data Type (ADT)
 *        using a circular array. The array will need to be resized if all the
 *        array slots are full.
 *****************************************************************************/
template <class T>
class Queue
{
public:
  // Define a "trait"
  typedef T element_type;

  // = Exceptions thrown by methods in this class.
  class Underflow {};

  // = Initialization, assignment, and termination methods.
  // Constructor.
  // Postcondition: The queue has been initialized as an empty queue.
  Queue (void);

  // Copy constructor.
  // Postcondition: The queue has been initialized with the queue argument
  //  passed in (i.e., same values, order, and number of elements).
  Queue (const Queue<T> &rhs);

  // Perform actions needed when queue goes out of scope.
  // Postcondition: Any allocated memory has been reclaimed/freed.
  ~Queue (void);

  // Assignment operator.
  // Postcondition: The queue has been assigned the queue argument
  //  passed in (i.e., same values, order, and number of elements).
  Queue<T> &operator = (const Queue<T> &rhs);

  // = Classic Queue operations.
  // Postcondition: A new copy of <new_item> is at the back of the queue.
  void enqueue (const T &new_item);

  // Precondition: size() > 0.
  // Postcondition: The front item on the queue has been removed.
  //   Throws the <Underflow> exception if the queue is empty.
  void dequeue (void);

  // Precondition: size() > 0.
  // Postcondition: Returns the first queue item.
  //   Throws the <Underflow> exception if the queue is empty.
  T first (void) const;

  // = Check boundary conditions for Queue operations.
  // Postcondition: Returns true if the queue is empty, false otherwise.
  bool is_empty (void) const;

  // Postcondition: Returns the current number of elements in the queue.
  size_t size (void) const;

  // Postcondition: Returns true if the
  //   size()'s of the two queues are equal and all the elements from the
  //   front of the queue to the end of the queue are equal, else false.
  bool operator== (const Queue<T> &rhs) const;

  // Postcondition: Returns false if the
  //   size()'s of the two queues are equal and all the elements from the
  //   front of the queue to the end of the queue are equal, else true.
  bool operator!= (const Queue<T> &rhs) const;

protected:
  // Precondition: The parameter passed in is a valid index into the data
  //  array.
  // Postcondition: Returns the next index to use in the array.
  size_t next_index (size_t index) const;

private:
  // circular array to contain the data
  T *data_;

  // The maximum number of items that the array can hold.
  size_t capacity_;

  // the index for the first element in the queue
  size_t first_;

  // the index for the last element in the queue
  size_t last_;

  // Number of items that are currently in the queue (for performance).
  size_t count_;
};


#include "queue-imp-fix2.cpp"

#endif /* QUEUE_T_H */
