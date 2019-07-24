Kevin Fernandes
December 2017

Here, we will go over the basic usage of the main file and the project. The
FSA is the only machine type available for emulation, since there is simply not
enough time left to complete such a task.

There are two main programs for the project: the test program and the main
program. The test program will simply test that the program functions properly.
The main program will provide the actual centerpiece of the project. The
program reads a text file with information about the machine and parsess it to
emulate the machine. The program then prompts the user for inputs to the
machine. The user can terminate the program at anytime during the prompt. 

The structure of the FSA file is as follows:

------------------------------ FILE FORMAT ------------------------------------

First, we declare the file contains information for a FSA by including the line
  FSA;

Then, we declare the alphabet of the machine with
  ALPHA : { symbol_0 symbol_1 symbol_2 ... symbol_n };
Note that with every keyword, like in this case "ALPHA", must be uppercase.
Also, every symbol in the ALPHA set must be one character long.

Next, we declare the set of states with
  STATE : { state_0 state_1 state_2 ... state_n };
Every state has a unique name with some whitespace between them.

We declare the set of final states similarly:
  FINAL : { final_0 final_1 final_2 ... final_n };
As with the normal definition of a FSA, FINAL is an improper subset of STATE.

The starting state is declared with the line
  START : state_0;
Here, we don't use the braket notation since the start state is a single state
and not a set of states.

Finally, we declare transitions for each state in STATE. The declaration is
as follows:
  state_0 : (state_1 symbol_0) (state_2 symbol_1) ... (state_n symbol_m);
This line declares transitions where state_0 is the state current state, 
state_n is the state being moved to, and symbol_m is the symbol on the
transition. There must be a transition for every symbol in ALPHA, and one
cannot use the same symbol twice in this definition.

Whitespace is allowed anywhere inbetween tokens (e.g. keywords, brackets, etc.)


The following is an example of a FSA that accepts the language of binary
strings (i.e. strings of 0's and 1's) with an odd number of 1's.

------------------------------- EXAMPLE ---------------------------------------

FSA;

ALPHA : { 0 1 };
STATE : { q0 q1 };
START : q0;
FINAL : { q1 };

q0 : (q0, 0) (q1, 1)
q1 : (q1, 0) (q0, 1)

----------------------------- END EXAMPLE -------------------------------------

