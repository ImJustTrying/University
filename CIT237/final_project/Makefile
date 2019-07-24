# Kevin Fernandes
# December 2017
#
# This is the make file for the project. Simply running `make` will compile
# both the test and the main program.

CC = g++
CFLAGS = -std=c++11 -g
OBJS = Set.o SymbolSet.o State.o Transition.o Stack.o StateSet.o Digraph.o \
			 FSA.o FSAParser.o
DEPS = Set.h SymbolSet.h State.h Transition.h Stack.h StateSet.h Digraph.h \
			 FSA.h Machine.h Dictionary.h FSAParser.h 

all : main test

main: main.o $(OBJS) $(DEPS)
	$(CC) -o main $< $(OBJS) $(CFLAGS)

main.o : main.cpp $(OBJS) $(DEPS)
	$(CC) -c $< $(CFLAGS)

test : test.o $(OBJS) $(DEPS)
	$(CC) -o test $< $(OBJS) $(CFLAGS)

test.o : test.cpp $(OBJS)
	$(CC) -c $< $(CFLAGS)


# Dependencies

Set.o : Set.cpp Set.h
	$(CC) -c $< $(CFLAGS)

SymbolSet.o : SymbolSet.cpp SymbolSet.h Set.o
	$(CC) -c $< $(CFLAGS)

Transition.o : Transition.cpp Transition.h
	$(CC) -c $< $(CFLAGS)

State.o : State.cpp State.h
	$(CC) -c $< $(CFLAGS)

Stack.o : Stack.cpp Stack.h
	$(CC) -c $< $(CFLAGS)

StateSet.o : StateSet.cpp StateSet.h State.o Set.o
	$(CC) -c $< $(CFLAGS)

Digraph.o : Digraph.cpp Digraph.h Transition.o State.o
	$(CC) -c $< $(CFLAGS)

FSA.o : FSA.cpp FSA.h Digraph.o Machine.h Dictionary.h
	$(CC) -c $< $(CFLAGS)

FSAParser.o : FSAParser.cpp FSAParser.h Machine.h FSA.o Dictionary.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o main test
