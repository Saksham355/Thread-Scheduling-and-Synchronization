## Question 1

### Description

Write a C program to simulate thread scheduling that ensures deadlock avoidance using a simplified resource allocation system. The goal is to avoid deadlock by controlling the order in which threads acquire locks, based on a predefined global knowledge of resources.

### Files

- `Q1.c`: Contains the main function and the implementation.

### Instructions

1. Create 3 threads (T1, T2, T3), and each thread needs to acquire 2 locks (Lock A and Lock B) in a specific order.
2. The threads should not be able to acquire locks in a way that causes the program to deadlock.
3. Implement deadlock avoidance using Resource Instance Ordering by enforcing a strict lock acquisition order (e.g., Lock A must always be acquired before Lock B).
4. Print messages showing the order of lock acquisition and thread waiting (e.g., "T1 acquired Lock A", "T2 waiting for Lock A").
5. The program should terminate after each thread has acquired each lock 3 times.


## Question 2

### Description

Write a multithreaded C program to simulate the Networked Servers Problem, a synchronization problem where servers are trying to access shared network resources. Use Semaphores to represent the network channels and ensure proper synchronization among the servers.

### Files

- `Q2.c`: Contains the main function and the implementation.

### Instructions

1. There are 5 servers in a data center, each trying to perform data processing tasks that require access to two network channels (left and right).
2. Each network channel is shared by 2 adjacent servers. The last network channel is shared by the last server and the first server.
3. A server can only process data when it has access to both its left and right network channels.
4. Each server takes 1 second to do data processing.
5. Maintain mutual exclusion and prevent resource starvation.
6. Print messages indicating when servers are waiting and processing.


## Question 3

### Description

Implement a C program that simulates the inventory management of a warehouse. The program should consist of two types of threads: Delivery Trucks and Storage Managers.

### Files

- `Q3.c`: Contains the main function and the implementation.

### Instructions

1. Implement a circular buffer to represent the storage area in the warehouse. The buffer should have a maximum capacity defined as a constant in the code.
2. Create multiple delivery truck threads that simulate trucks arriving at the warehouse at random intervals, delivering a random number of products.
3. Create multiple storage manager threads that simulate the storage of products at random intervals, taking a random number of products from the warehouse.
4. Use semaphores/mutexes to coordinate access to the shared storage buffer.
5. Print messages indicating the current inventory status after each delivery and storage operation.


## Question 4

### Description

This question is divided into two parts:

1. Implement a program in C that performs matrix multiplication using multiple threads.
2. Implement a thread pool that will reuse threads for computing each element of Matrix C.

### Files

- `Q4i.c`: Contains the main function and implementation for part 1.
- `Q4ii.c`: Contains the main function and implementation for part 2.

### Instructions

#### Part 1

1. Input: Matrix A (size: m x n), Matrix B (size: n x p), Resultant matrix C (m x p).
2. Create a suitable number of threads based on the size of the resultant matrix, allowing each thread to calculate one element of Matrix C.
3. Allocate matrices dynamically based on user input.
4. Print the resultant matrix C along with the speed-up over the sequential version.


#### Part 2

1. Implement a thread pool that can manage a fixed number of threads using the pthreads API.
2. Each thread in the pool should be capable of performing a single task to compute one element of the resultant matrix C.
3. Design the thread pool API as a generic API that accepts a callback with some data as input and runs the callback with data.







