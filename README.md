##README FILE - Generic Container

##Project Overview:
`MyContainer` is a generic C++ container class template that holds objects—types that support equality and all relational comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`). The container supports adding, removing, and printing elements, and provides multiple custom iterator classes to traverse its contents in various orders.

##Setup and Compilation
To compile and run the project, follow these steps:
1. Clone the repository.
2. Compile the code use a C++20 or later (for concepts and modern language features) compiler.
3. Options: 
make Main- to run the main file.
make test- to run the unit test.
make valgrind- memory leak testing using valgrind for main.
make valgrind_test- memory leak testing using valgrind for test.
make clean- deletes all irrelevant files after running.

## Features

- Supports any type `T` that satisfies the **TotallyOrderedWith** concept (fully ordered types).
- Dynamic resizing of internal storage based on usage (capacity doubles when 75% full, halves when 25% full).
 
##Class MyContainer<T>

Functions:
- add(T& newObj) - Add elements with automatic capacity management.
- remove(T& obj) - Remove all occurrences of a given element.
-size() - Returns the number of elements.
- get(int i) - Access elements by index.
-operator<<(std::ostream& os, const MyContainer& m) -  Stream output operator to print container contents.
getCapacity() — Returns current capacity (for testing).

Iterators:
- Multiple iterator classes for different traversal orders:
  - **Order**: Iterates elements in insertion order.
  - **ReverseOrder**: Iterates elements in reverse insertion order.
  - **AscendingOrder**: Iterates elements from smallest to largest.
  - **DescendingOrder**: Iterates elements from largest to smallest.
  - **SideCrossOrder**: Alternates between smallest and largest remaining elements.
  - **MiddleOutOrder**: Starts from the middle element, moving left and right alternately.
