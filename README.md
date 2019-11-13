# Queue-Implementation
Implementation and testing for a templatized queue class

# Queue-Implementation
Implementation and testing for a templatized queue class

1. The Assignment: You will implement a queue class using a circular array (as discussed in class) as well as test your queue class.
2. Purposes:
    Ensure that you are familiar with the queue data structure,
    Implement a circular array and use it with a queue, and
    Gain additional experience with:
    a. implementing and using template code and
    b. creating and throwing exceptions.
3. Evaluation & Description:
    a. (50%) In class we’ve been discussing circular arrays and how we could implement a circular array to provide more flexibility in the data structures that we use. In this lab you are provided with a skeleton for a Queue class which uses a circular array to manage the data. Descriptions for methods and data members are included. Your assignment is to implement the methods for this class. Be sure to add your name, step/exercise, the course number, and an integrity statement. You can find links to the needed files below:
    Queue_T.h
    Queue_T.cpp
    Queue_T-Test.cpp
    b. (50%) You will also need to design and implement code to test your Queue class. At a minimum, the tests should cover all public methods of the class. Rather than using assert functionality as was done in the past, you should now throw exceptions. You should also generate test cases where you expect exceptions to be thrown (and handle the exceptions appropriately). Please think about the many tests that can be performed. The comments in the testing file above give you some ideas and you need to start with these tests but they are not comprehensive or exhaustive.
    i. 0 – 5 tests – 25% of this portion of the grade
    ii. 6 – 10 tests – 50% of this portion of the grade
    iii. 11 – 15 tests – 75% of this portion of the grade
    iv. 16 – 20 tests – 100% of this portion of the grade
    c. As before, in addition to testing functionality you will need to use a memory checker to make sure you are handling dynamically allocated memory correctly. On Linux, you can use valgrind. Up to 20% of the possible points will be deducted for memory leaks or problems.
    d. Consistent formatting, indentation, and documentation/commenting. Up to 20% of the possible points will be deducted for inconsistencies in these areas.
Your programs will be graded on implementing the appropriate functionality as described above as well as the coding practices discussed in class and listed on the website, such as,
     no compilation warnings
     consistent style such as indentation, upper case for types, designation of member variables (e.g., using “_” at the end of the name)
     modular design,
     encapsulation,
     appropriate comments and documentation,
     no magic numbers (e.g., if (j < 42))
     no macros (other than to #include header files and provide header inclusion guards)
     using const methods where appropriate
     using operator overloading where appropriate and provide negation operators if appropriate (e.g., == and !=)
     using member initialization lists for constructors
     not using C style casts (i.e., use static_cast<>, const_cast<>, dynamic_cast<>, or reinterpret_cast<>)
