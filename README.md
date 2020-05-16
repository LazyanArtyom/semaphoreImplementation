# Semaphore Implementation

## What is a Critical Section?
A critical section is a section of code that can only be executed by one thread at a time, if the program is to function correctly. If two threads (or processes) were to execute code inside the critical section at the same time then it is possible that program may no longer have correct behavior.

## What is a Semaphore
Semaphores are integer variables that are used to solve the critical section problem by using two atomic operations, wait and signal that are used for process synchronization.

## When to use semaphore?
Semaphores are commonly use for two purposes: to share a common memory space and to share access to files. Semaphores are one of the techniques for interprocess communication (IPC). The C programming language provides a set of interfaces or "functions" for managing semaphores.

## Compilation
> gcc main.cpp -o out -pthread
