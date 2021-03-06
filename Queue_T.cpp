// File: Queue_T.cpp
//
// Author: Micah Withers
// Course: CIS-221
// Assignment: Queue implementation using a dynamic circular array
//
//I typed all of this code on my own, I did not show my code
//      to anyone, I did not look at anyone else's code, and no
//      code was copied.
//
// Purpose: Implementation file for templatized queue class.
// This file includes method implementations for a Queue.

#ifndef QUEUE_T_CPP
#define QUEUE_T_CPP

#include "Queue_T.h"


/*****************************************************************************
 * Queue Method Implementations
 *****************************************************************************/
// Constructor.
// Postcondition: The queue has been initialized as an empty queue.
template <class T>
Queue<T>::Queue ()
  :	data_(new T[DEFAULT_CAPACITY]), capacity_(DEFAULT_CAPACITY), first_(0), last_(capacity_-1), count_(0)
{
}

// Copy constructor.
// Postcondition: The queue has been initialized with the queue argument
//  passed in (i.e., same values, order, and number of elements).
template <class T>
Queue<T>::Queue (const Queue<T> &rhs)
  :	data_(new T[rhs.capacity_]), capacity_(rhs.capacity_), first_(rhs.first_), last_(rhs.last_), count_(rhs.count_)
{
	std::copy(rhs.data_, rhs.data_ + rhs.count_, data_);	//	Copies values from rhs and sets data member values.
}

// Destructor
// Postcondition: Any allocated memory has been reclaimed/freed.
template <class T>
Queue<T>::~Queue (void)
{
	delete [] data_;
}

// Assignment operator.
// Postcondition: The queue has been assigned the queue argument
//  passed in (i.e., same values, order, and number of elements).
template <class T>
Queue<T> &
Queue<T>::operator= (const Queue<T> &rhs)
{
	if (this != &rhs) {						//	Checks for self-assignment.
    if (this->capacity_ < rhs.count_) {				//	Resizes array if its capacity is less than that of rhs.
      T *new_data = new T[rhs.count_];
      delete [] data_;      //	Has data_ point to new array after releasing the memory of the original array.
      data_ = new_data;
      capacity_ = rhs.capacity_;
    }
    size_t start = rhs.first_;
    for (size_t i = 0; i < rhs.count_; ++i) {	//	Copies values from rhs (first_ to last_) to a data_, starting at index 0.
      data_[i] = rhs.data_[start];
      start = rhs.next_index(start);
    }
    first_ = 0;
    last_ = rhs.count_-1;
    this->count_ = rhs.count_;
  }
	return *this;
}

// Postcondition: A new copy of <new_item> is at the back of the queue.
template <class T>
void
Queue<T>::enqueue (const T &new_item)
{
	if (count_ == capacity_) {					//	Resizes array if it is at capacity.
		T *new_data = new T[capacity_*2];
		size_t start = first_;
		for (size_t i = 0; i < count_; ++i) {	//	Copies values (first_ to last_) to a new array.
			new_data[i] = data_[start];
			start = next_index(start);
		}
		delete [] data_;
		data_ = new_data;		//	Has data_ point to new array and sets first_ and last_ (after releasing the memory of the original array).
    capacity_ *= 2;
    first_ = 0;
		last_ = count_-1;
	}
	last_ = next_index(last_);	//	Increments last_, inserts the value at last_ index, then increments count.
	data_[last_] = new_item;
	++count_;
}

// Precondition: size() > 0.
// Postcondition: The front item on the queue has been removed.
//   Throws the <Underflow> exception if the queue is empty.
template <class T>
void
Queue<T>::dequeue (void)
{
	count_ == 0 ? throw Underflow( ) : 	--count_;
	first_ = next_index(first_);	//	Increments first_, then decrements count_.
}

// Precondition: size() > 0.
// Postcondition: Returns the first queue item.
//   Throws the <Underflow> exception if the queue is empty.
template <class T>
T
Queue<T>::first (void) const
{
	return count_ == 0 ? throw Underflow( ) : data_[first_];
}

// Postcondition: Returns true if the queue is empty, false otherwise.
template <class T>
bool
Queue<T>::is_empty (void) const
{
	return count_ == 0;
}

// Postcondition: Returns the current number of elements in the queue.
template <class T>
size_t
Queue<T>::size (void) const
{
	return count_;
}

// Postcondition: Returns true if the
//   size()'s of the two queues are equal and all the elements from 0
//   .. size()-1 are equal, else false.
template <class T>
bool
Queue<T>::operator== (const Queue<T> &rhs) const
{
	if (this->count_ == rhs.count_) {			//	Checks that sizes are equal (returns false if not equal).
  	size_t start1 = this->first_;				//	Creates variables to iterate through both queues from start
  	size_t start2 = rhs.first_;					//		to end (first_ to last_) and returns false if any values are
  	for (size_t i = 0; i < count_; ++i) {		//		not equal.
  		if (this->data_[start1] != rhs.data_[start2]) {
  			return false;
  		}
  		start1 = this->next_index(start1);
  		start2 = rhs.next_index(start2);
  	}
  	return true;
  }
  return false;
}

// Postcondition: Returns false if the
//   size()'s of the two queues are equal and all the elements from 0
//   .. size()-1 are equal, else true.
template <class T>
bool
Queue<T>::operator!= (const Queue<T> &rhs) const
{
	return !(*this == rhs);
}

// Precondition: The parameter passed in is a valid index into the data
//  array.
// Postcondition: Returns the next index to use in the array.
template <class T>
size_t
Queue<T>::next_index (size_t index) const
{
	return index < capacity_ ? (++index) % capacity_ : throw InvalidIndex( );
}

#endif /* QUEUE_T_CPP */
