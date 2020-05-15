# Semaphore Implementation

**What is a Critical Section?**
A critical section is a section of code that can only be executed by one thread at a time, if the program is to function correctly. If two threads (or processes) were to execute code inside the critical section at the same time then it is possible that program may no longer have correct behavior.


**Compilation**
> gcc main.cpp -o out -pthread
