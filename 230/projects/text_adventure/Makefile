SRC = rooms.c items.c adventure.c
OBJ = rooms.o items.o adventure.o
PROG = adventure.out

$(PROG) : $(OBJ)
	gcc -g adventure.o items.o rooms.o -o adventure.out

$(OBJ) : $(SRC)
	gcc -g -c items.c;
	gcc -g -c rooms.c;
	gcc -g -c adventure.c;

clean :
	rm *.o *.out
