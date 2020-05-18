My implementation of wordfreak is composed of 3 files: word_freak.c which contains the main
functionality, table.h which contains definitions and function prototypes for a sorted doubly
linked list, and table.c which contains implementations for those functions in table.h.
The program produces the correct output as far as I can tell (at least for the sample texts
supplied). My use of the sorted doubly linked list (table) is explained in table.h, and the list
is used in the word_freak.c file to store the words and their associated frequencies. Helper
functions are also used (e.g. tolower() or num_to_string()) for the purposes of printing to stdout
via system calls.

Video: https://youtu.be/SfZ4R5PPliw
