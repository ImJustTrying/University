The jimmy_fallon.c file contains my implementation of the ticket distribution program. There are
only two functions: main and phone_call, with the later being the thread function. One of the notable
things about the program are that all of the semaphores are in global scope. I tried making the
semaphores static but there was no consistent way (that I could think of) to initialize and
destroy them without introducing race conditions. Another is the realization that I can read from
shared memory (e.g. 'connected' or 'tickets_given') without introducing race conditions so long as
I always use a semaphore to write to the memory location. This made writing the program much
simpler than I initially thought, since checking the state of a variable does not require locking
it under a semaphore and thereby slowing the program down significantly. Finally, I allowed the
program to take in a variable number of callers, and thereby adding another layer of checks for the
number of tickets sold (and in fact another semaphore for updating that variable).

Video: https://youtu.be/-ZzzVUA0DEw
