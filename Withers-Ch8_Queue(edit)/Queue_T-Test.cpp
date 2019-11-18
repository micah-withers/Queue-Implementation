// File: Queue_T-Test.cpp
//
// Author: Micah Withers
// Course: CIS-221
// Assignment: Queue implementation using a dynamic circular array
//
//I typed all of this code on my own, I did not show my code
//      to anyone, I did not look at anyone else's code, and no
//      code was copied.
//
// Purpose: Testing file for templatized queue class.

// Standard headers
#include <iostream>
#include "Queue_T.h"

//	This typedef is useful if you want to queue doubles.
typedef double value_type;
typedef Queue<value_type> CQUEUE;
size_t DEFAULT_CAPACITY = CQUEUE::DEFAULT_CAPACITY;

//Postcondition: values from elements[] are added to the queue (from elements[0] to elements[size]).
void enqueue_elements (CQUEUE& queue, value_type elements[], size_t size) {	//	Inputs values from elements[] into the queue
	for (size_t i = 0; i < size; ++i) {
		queue.enqueue(elements[i]);
	}
}

//	Postcondition: returns true if the values of queue and elements[] are the same
//		and in the same order, otherwise returns false.
bool check_accuracy (const CQUEUE& queue, value_type elements[], size_t size) {		//	Compares the values in the queue to those in elements[]
	CQUEUE copy_queue(queue);											//	Copies the queue so the original is unaffected
	if (copy_queue.size( ) != size) {
		std::cout << "Size of queue (" << copy_queue.size( ) << ") should be ("
			<< size << ")." << std::endl;
		return false;
	}
	size_t i = 0;
	try {
		while (i < size) {
			if (copy_queue.first( ) != elements[i]) {		//	Prints values if they are unequal and returns false, or removes them if they are equal
				std::cout << "Element read (" << copy_queue.first( ) << "), should be ("
					<< elements[i] << ")." << std::endl;
				return false;
			}
			copy_queue.dequeue( );
			++i;
		}
	}
	catch (CQUEUE::Underflow) {
		std::cout << "CQUEUE::Underflow exception: cannot dequeue from an empty queue." << std::endl;
		return false;
	}
	return true;
}

//	Postcondition: prints "Test {test_num} passed/failed" if pass is true/false
//		and adds 1 to progress[0] if passed or adds 1 to progress[1] if failed.
void pass_fail (bool pass, int test_num, int progress[]) {
	if (pass) {
		std::cout << "passed.";
		++progress[0];
		return;
	}
	std::cout << "failed.";
	++progress[1];
}

  //===================================================
  // Tests 1-4 Enqueue, dequeue, and first tests
  //===================================================
void basic_tests(int progress[], size_t elem_size, value_type elements[]) {

  // Test 1: 	dequeueing an element from an empty queue.
	bool pass = true;
	std::cout << "Test 1: dequeueing an element from an empty queue . . ." << std::endl;
	CQUEUE test1;

	try {				//	dequeue( ) throws an Underflow exception if the queue is empty
		test1.dequeue( );
		pass = false;
	}
	catch (CQUEUE::Underflow) {
		std::cout << "CQUEUE::Underflow exception: cannot dequeue from an empty queue." << std::endl;
	}
	pass_fail(pass, progress[0]+progress[1], progress);	//	Records and prints results of the test
	std::cout << std::endl << std::endl;

  // Test 2: 	enqueueing several values into an empty queue.
	pass = true;
	std::cout << "Test 2: enqueueing several values into an empty queue . . ." << std::endl;
	CQUEUE test2;

	enqueue_elements(test2, elements, elem_size);			//	Pushes values onto the queue, then checks the queue for accuracy
	if (!check_accuracy(test2, elements, elem_size)) {
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

  // Test 3: 	dequeueing first few elements (and checking for accuracy of enqueue).
  pass = true;
	std::cout << "Test 3: dequeueing first few elements . . ." << std::endl;
	CQUEUE test3;
	enqueue_elements(test3, elements, elem_size);		//	Pushes item onto the queue

	for (size_t i = 0; i < elem_size-1; ++i) {		//	All but one item are checked for accuracy then dequeueed
		if (test3.first( ) != elements[i]) {
			std::cout << "Element read (" << test3.first( ) << "), should be ("
				<< elements[i] << ")." << std::endl;
			pass = false;
		}
		test3.dequeue( );
	}
	if (test3.first( ) != elements[elem_size-1]) {				//	Checks last item for accuracy (it is not removed)
		std::cout << "Element read (" << test3.first( ) << "), should be ("
				<< elements[elem_size-1] << ")." << std::endl;
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

  // Test 4: 	alternating enqueue and dequeue, checking for accuracy.
	pass = true;
	std::cout << "Test 4: alternating enqueue and dequeue, checking for accuracy . . ." << std::endl;
	CQUEUE test4;
						//	Elements are enqueueed and dequeueed to and from the queue and
						//		periodically checked for accuracy.
	value_type first = 10;	//	Will contain what should be the first value in the queue
	value_type next = 1;		//	Contains the next value to be added to the queue
	size_t count = 0;				//	Tracks the number of items expected to be in the queue

	while (count < DEFAULT_CAPACITY/2) {
		test4.enqueue(next*10);							//	Enqueues values
		++count;
		++next;
	}
	if (test4.first( ) != first) {			//	Checks first item for accuracy
		std::cout << "Element read (" << test4.first( ) << "), should be ("
				<< first << ")." << std::endl;
		pass = false;
	}
	if (test4.size( ) != count) {				//	Checks number of items for accuracy
		std::cout << "Number of elements (" << test4.size( ) << "), should be ("
				<< count << ")." << std::endl;
		pass = false;
	}

	while (count > (DEFAULT_CAPACITY/2)/2) {		//	Dequeues items
		test4.dequeue( );
		--count;
		first += 10;
	}
	if (test4.first( ) != first) {
		std::cout << "Element read (" << test4.first( ) << "), should be ("
				<< first << ")." << std::endl;
		pass = false;
	}
	if (test4.size( ) != count) {
		std::cout << "Number of elements (" << test4.size( ) << "), should be ("
				<< count << ")." << std::endl;
		pass = false;
	}

	while (count < DEFAULT_CAPACITY) {		//	Enqueues items
		test4.enqueue(next*10);
		++count;
		++next;
	}
	if (test4.first( ) != first) {
		std::cout << "Element read (" << test4.first( ) << "), should be ("
				<< first << ")." << std::endl;
		pass = false;
	}
	if (test4.size( ) != count) {
		std::cout << "Number of elements (" << test4.size( ) << "), should be ("
				<< count << ")." << std::endl;
		pass = false;
	}

	while (count > (DEFAULT_CAPACITY/2)) {	//	Dequeues items
		test4.dequeue( );
		--count;
		first += 10;
	}
	if (test4.first( ) != first) {
		std::cout << "Element read (" << test4.first( ) << "), should be ("
				<< first << ")." << std::endl;
		pass = false;
	}
	if (test4.size( ) != count) {
		std::cout << "Number of elements (" << test4.size( ) << "), should be ("
				<< count << ")." << std::endl;
		pass = false;
	}

	while (count < DEFAULT_CAPACITY) {		//	Enqueues items
		test4.enqueue(next*10);
		++count;
		++next;
	}
	if (test4.first( ) != first) {
		std::cout << "Element read (" << test4.first( ) << "), should be ("
				<< first << ")." << std::endl;
		pass = false;
	}
	if (test4.size( ) != count) {
		std::cout << "Number of elements (" << test4.size( ) << "), should be ("
				<< count << ")." << std::endl;
		pass = false;
	}

	value_type elements4[count];
	for (size_t i = 0; i < count; ++i) {		//	Adds elements to an array that are expected to be in the queue
		elements4[i] = first;
		first += 10;
	}
	pass = check_accuracy(test4, elements4, count);
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;
}

  //===================================================
  // Tests 5-7 CQUEUE::Underflow tests
  //===================================================
void underflow_tests(int progress[], size_t elem_size, value_type elements[]) {

  // Test 5: 	checks queues for being empty.
	bool pass = true;
	std::cout << "Test 5: checks queues for being empty . . ." << std::endl;
	CQUEUE empty5;		//	An empty queue is created without adding values and tested for being empty.
	CQUEUE test5;		//	A queue is created and values are added and then tested for being empty.
	enqueue_elements(test5, elements, elem_size);

	if (!empty5.is_empty( )) {
		std::cout << "is_empty should return true, but it returned false." << std::endl;
	}

	if(test5.is_empty( )) {
		std::cout << "is_empty should return false, but it returned true." << std::endl;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

  // Test 6: 	dequeueing all elements until we get an Underflow exception.
	pass = true;
	std::cout << "Test 6: dequeueing all elements until we get an Underflow exception . . ." << std::endl;
	CQUEUE test6;
	enqueue_elements(test6, elements, elem_size);
	try {
		while (test6.size( ) >= 0) {		//	A queue with values is dequeueed until Underflow is thrown.
			test6.dequeue( );
		}
		pass = false;
	}
	catch (CQUEUE::Underflow) {
		std::cout << "CQUEUE::Underflow exception: cannot dequeue from an empty queue" << std::endl;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

  // Test 7: 	testing that first will throw an Underflow exception on an empty queue.
	pass = true;
	std::cout << "Test 7: testing that first will throw an Underflow exception on an empty queue . . ." << std::endl;
	CQUEUE test7;

	try {
		test7.first( );		//	first( ) is called on an empty queue and Underflow is expected to be thrown.
		pass = false;
	}
	catch (CQUEUE::Underflow) {
		std::cout << "CQUEUE::Underflow exception: cannot retrieve an item from an empty queue." << std::endl;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;
}

  //===================================================
  // Tests 8-11 Equality and inequality tests
  //===================================================
void equality_tests(int progress[], size_t elem_size, value_type elements[]) {

  // Test 8: 	test equality and inequality operators on empty queues.
	bool pass = true;
	std::cout << "Test 8: test equality and inequality operators on empty queues . . ." << std::endl;
	CQUEUE empty8a;
	CQUEUE empty8b;		//	Two empty queues are created and checked for equality

	if (!(empty8b == empty8a && empty8a == empty8b)) {
		std::cout << "The operator == returned false when it should return true." << std::endl;
		pass = false;
	}
	if (empty8b != empty8a || empty8a != empty8b) {
		std::cout << "The operator == returned true when it should return false." << std::endl;
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

  // Test 9: 	test equality and inequality operators on non-empty queues of equal values and sizes.
	pass = true;
	std::cout << "Test 9: test equality and inequality operators on non-empty queues of equal values and sizes . . ." << std::endl;
	CQUEUE test9a;
	CQUEUE test9b;
	enqueue_elements(test9a, elements, elem_size);		//	Values are added to two queues in the same order
	enqueue_elements(test9b, elements, elem_size);		//		then checked for equality.

	if (!(test9b == test9a && test9a == test9b)) {
		std::cout << "The operator == returned false when it should return true." << std::endl;
		pass = false;
	}
	if (test9b != test9a || test9a != test9b) {
		std::cout << "The operator != returned true when it should return false." << std::endl;
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

  // Test 10: 	test equality and inequality operators on non-empty queues of equal sizes and unequal values.
	pass = true;
	std::cout << "Test 10: test equality and inequality operators on non-empty queues of equal sizes and unequal values . . ." << std::endl;
	CQUEUE test10a;
	CQUEUE test10b;

	enqueue_elements(test10a, elements, elem_size);		//	Differing values are added to two queues (same number of values),
	value_type value = 1;									//		then checked for equality.
	while (test10b.size( ) != test10a.size( )) {
		test10b.enqueue(value++);
	}

	if (test10b == test10a || test10a == test10b) {
		std::cout << "The operator == returned true when it should return false." << std::endl;
		pass = false;
	}
	if (!(test10b != test10a && test10a != test10b)) {
		std::cout << "The operator != returned false when it should return true." << std::endl;
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

  // Test 11: 	test equality and inequality operators on non-empty queues of unequal sizes.
	pass = true;
	std::cout << "Test 11: test equality and inequality operators on non-empty queues of unequal sizes . . ." << std::endl;
	CQUEUE test11a;
	CQUEUE test11b;

	enqueue_elements(test11a, elements, elem_size);	//	Values are added to two queues in the same order.
	enqueue_elements(test11b, elements, elem_size);
	test11b.enqueue(elements[elem_size-1]+10);								//	An extra value is added to the second queue, then
													//		both are checked for equality.
	if (test11b == test11a || test11a == test11b) {
		std::cout << "The operator == returned true when it should return false." << std::endl;
		pass = false;
	}
	if (!(test11b != test11a && test11a != test11b)) {
		std::cout << "The operator != returned false when it should return true." << std::endl;
		pass = false;
	}

	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;
}

  //===================================================
  // Tests 12-13 Copy constructor tests
  //===================================================
void copy_constr_tests(int progress[], size_t elem_size, value_type elements[]) {

  // Test 12: 	constructing a copy of an empty queue.
	bool pass = true;
	std::cout << "Test 12: constructing a copy of an empty queue . . ." << std::endl;
	CQUEUE empty12;
	CQUEUE test12(empty12);		//	test12 is constructed as a copy of empty12.

	if (test12 != empty12) {
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;


  // Test 13: 	constructing a copy of a non-empty queue.
  pass = true;
	std::cout << "Test 13: constructing a copy of a non-empty queue . . ." << std::endl;
	CQUEUE test13a;
	enqueue_elements(test13a, elements, elem_size);
	CQUEUE test13b(test13a);	//	test13b is constructed as a copy of test13a.

	if (test13b != test13a) {
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;
}

  //===================================================
  // Tests 14-18 Assignment operator tests
  //===================================================
void assignment_tests(int progress[], size_t elem_size, value_type elements[]) {

  // Test 14: 	checking for self-assignment.
  bool pass = true;
	std::cout << "Test 14: checking for self-assignment . . ." << std::endl;
	CQUEUE test14a;		//	Two queues are created and same values are added.
	CQUEUE test14b;
	enqueue_elements(test14a, elements, elem_size);
	enqueue_elements(test14b, elements, elem_size);

	test14a = test14a;			//	test14a is assigned to itself, then compared to test14b
	if (test14a != test14b) {	//		to determine if test14a had changed.
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

  // Test 15: 	assigning an empty queue to a non-empty queue.
	pass = true;
	std::cout << "Test 15: assigning an empty queue to a non-empty queue . . ." << std::endl;
	CQUEUE empty15;
	CQUEUE test15;
					//	empty15 remains empty, and values are added test15.
	enqueue_elements(test15, elements, elem_size);
	test15 = empty15;	//	test15 is assigned empty15, then checked for equality.

	if (test15 != empty15) {
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

  // Test 16: 	assigning a non-empty queue to an empty queue.
	pass = true;
  std::cout << "Test 16: assigning a non-empty queue to an empty queue . . ." << std::endl;
	CQUEUE test16;
	CQUEUE empty16;
										//	empty16 remains empty, values added to test16.
	enqueue_elements(test16, elements, elem_size);
	empty16 = test16;	//	empty16 is assigned test16, then checked for accuracy and equality.

	pass = check_accuracy(empty16, elements, elem_size);
	if (empty16 != test16) {
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

  // Test 17: 	assigning a non-empty queue to another non-empty queue of equal size.
	pass = true;
	std::cout << "Test 17: assigning a non-empty queue to another non-empty queue of equal size . . ." << std::endl;
	CQUEUE test17a;
	CQUEUE test17b;

	enqueue_elements(test17a, elements, elem_size);		//	Adds 3 values to the queue
	value_type value = 1;
	while (test17b.size( ) < test17b.size( )) {
		test17b.enqueue(value++);
	}

	test17b = test17a;		//	test17b is assigned test17a, then checked for equality.
	if (test17a != test17b) {
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

// Test 18: 	assigning a non-empty queue to another non-empty queue of unequal size.
	pass = true;
	std::cout << "Test 18: assigning a non-empty queue to another non-empty queue of unequal size . . ." << std::endl;
	CQUEUE test18a;
	CQUEUE test18b;

	enqueue_elements(test18a, elements, elem_size);
	value = elements[elem_size-1] + 10;
	while (test18b.size( ) < test18a.size( ) + 3) {
		test18b.enqueue(value);
		value += 10;
	}

	test18b = test18a;		//	test18b is assigned test18a, then checked for equality.
	if (test18a != test18b) {
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;
}

  //===================================================
  // Tests 19-20 Resizing Tests
  //===================================================
void resize_tests(int progress[], size_t elem_size, value_type elements[]) {

	// Test 19: 	test resizing by adding 30 values (10 is the default capacity).
	bool pass = true;
	std::cout << "Test 19: test resizing by adding a number of values equal to three times the default capacity . . ." << std::endl;
	CQUEUE test19;
	size_t size19 = 3*DEFAULT_CAPACITY;
	value_type elements19[size19];
	for (size_t i = 1; i < size19+1; ++i) {		//	Values are enqueued to the queue and added to the array
		test19.enqueue(i*10);					//		in the same order
		elements19[i-1] = i*10;
	}

	pass = check_accuracy(test19, elements19, size19);	//	Checking for accuracy
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;

// Test 20: 	test resizing by assigning a queue to another queue that has insufficient capacity.
	pass = true;
	std::cout << "Test 20: test resizing by assigning a queue to another queue that has insufficient capacity . . ." << std::endl;
	CQUEUE test20a;
	CQUEUE test20b;

	size_t size20 = 3*DEFAULT_CAPACITY;							//	More values than original capacity added to test20a
	value_type value = 10;
	while (test20a.size( ) < size20) {
		test20a.enqueue(value);
		value += 10;
	}
	enqueue_elements(test20b, elements, elem_size);	//	Less values than original capacity added to test20b

	test20b = test20a;			//	test20a is assigned to test20b, then checked for equality
	if (test20b != test20a) {
		pass = false;
	}
	pass_fail(pass, progress[0]+progress[1], progress);
	std::cout << std::endl << std::endl;
}

int
main (int argc, char *argv[])
{
	int progress[] = {0, 0}; // [0] passes index, [1] fails count
	size_t elem_size = 7;
	value_type elements[elem_size];
	for (size_t i = 1; i <= elem_size; ++i) {
		elements[i-1] = i*10;
	}

  //=============================================================
  //=============================================================
  //					BEGIN TESTING

	std::cout << std::endl << "Running tests" << std::endl << std::endl;

	basic_tests(progress, elem_size, elements);			// Tests 1-4 	Enqueue, dequeue, and first tests
	underflow_tests(progress, elem_size, elements);		// Tests 5-7 	CQUEUE::Underflow tests
	equality_tests(progress, elem_size, elements);		// Tests 8-11 	Equality and inequality tests
	copy_constr_tests(progress, elem_size, elements);	// Tests 12-13 	Copy constructor tests
	assignment_tests(progress, elem_size, elements);	// Tests 14-18 	Assignment operator tests
	resize_tests(progress, elem_size, elements);		// Tests 19-20 	Resizing Tests

  //					END TESTING
  //=============================================================
  //=============================================================
	std::cout << "Testing complete." << std::endl;
	std::cout << progress[1] << " test(s) failed." << std::endl;
	std::cout << progress[0] << " test(s) passed." << std::endl;

	return EXIT_SUCCESS;
}
