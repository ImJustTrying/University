CC = gcc
FLAGS = -g -lm 
OBJS = table.o
DEPS = table.h table.c

all : word_freak.c $(OBJS)
	$(CC) word_freak.c -o wordfreak $(OBJS) $(FLAGS) 

$(OBJS) : $(DEPS)
	$(CC) -c table.c $(FLAGS)

clean :
	rm *.o wordfreak
