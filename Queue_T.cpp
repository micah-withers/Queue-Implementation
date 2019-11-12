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
  :	capacity_(10), first_(0), last_(capacity_-1), count_(0)
{
	data_ = new T[capacity_];
}

// Copy constructor.
// Postcondition: The queue has been initialized with the queue argument
//  passed in (i.e., same values, order, and number of elements).
template <class T>
Queue<T>::Queue (const Queue<T> &rhs)
  :	data_(new T[rhs.capacity_]), capacity_(rhs.capacity_), first_(rhs.first_), last_(rhs.last_), count_(rhs.count_)
{
	std::copy(rhs.data_, rhs.data_ + rhs.size( ), data_);	//	Copies values from rhs and sets data member values.
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
	if (this == &rhs) {						//	Checks for self-assignment.
		return *this;
	}
	if (this->size( ) < rhs.size( )) {		//	Resizes array if necessary.
		delete [] data_;
		this->data_ = new T[rhs.size( )];
		this->capacity_ = rhs.capacity_;
	}
	std::copy(rhs.data_, rhs.data_ + rhs.size( ), data_);	//	Copies values from rhs and sets data member values.
	this->first_ = rhs.first_;
	this->last_ =  rhs.last_;
	this->count_ = rhs.count_;
	return *this;
}

// Postcondition: A new copy of <new_item> is at the back of the queue.
template <class T>
void
Queue<T>::enqueue (const T &new_item)
{
	if (size( ) == capacity_) {					//	Resizes array if it is at capacity.
		T *new_data = new T[capacity_+1];
		size_t copy_index = first_;
		size_t many_items = 0;
		while (many_items < size( )) {
			new_data[many_items] = data_[copy_index];	//	Copies values (first_ to last_) to a new array.
			copy_index = next_index(copy_index);
			if (copy_index == capacity_) {
				copy_index = 0;
			}
			++many_items;
		}
		delete [] data_;		//	Has data_ point to new array and sets first_ and last_
		data_ = new_data;		//		(after releasing the memory of the original array).
		first_ = 0;
		last_ = capacity_-1;
		++capacity_;
	}
	last_ = next_index(last_);	//	Increments last_, inserts the value at last_ index, then increments count.
	if (last_ == capacity_) {
		last_ = 0;
	}
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
	if (is_empty( )) {
		throw Underflow( );
	}
	first_ = next_index(first_);	//	Increments first_, then decrements count_.
	if (first_ == capacity_) {
		first_ = 0;
	}
	--count_;
}

// Precondition: size() > 0.
// Postcondition: Returns the first queue item.
//   Throws the <Underflow> exception if the queue is empty. 
template <class T>
T 
Queue<T>::first (void) const
{
	if (is_empty( )) {
		throw Underflow( );
	}
	return data_[first_];
}

// Postcondition: Returns true if the queue is empty, false otherwise. 
template <class T>
bool
Queue<T>::is_empty (void) const 
{
	if (size( ) == 0) {
		return true;
	}
	return false;
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
	if (this->size( ) != rhs.size( )) {			//	Checks that sizes are equal (returns false if not equal).
		return false;
	}
	size_t start1 = this->first_;				//	Creates variables to iterate through both queues from start
	size_t start2 = rhs.first_;					//		to end (first_ to last_) and returns false if any values are
	for (size_t i = 0; i < size( ); ++i) {		//		not equal.
		if (this->data_[start1] != rhs.data_[start2]) {
			return false;
		}
		start1 = this->next_index(start1);
		start2 = rhs.next_index(start2);
	}
	return true;
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
	return ++index;
  // You should just need one line of code.
}

#endif /* QUEUE_T_CPP */