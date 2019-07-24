OBJS = Day.o CashRegister.o Item.o CreditCard.o Money.o
DEPS = Day.h CashRegister.h Item.h CreditCard.h Money.h Peso.h Euro.h Ruble.h \
			 Dollar.h Pound.h CanadianDollar.h

ADMIN_DEPS = Password.h Day.h
ADMIN_OBJS = Password.o

CC = g++
CFLAGS = -g -std=c++11

all : bakery admin

# rules for bakery program
bakery : bakery.o $(OBJS) $(DEPS)
	$(CC) -o bakery $< $(OBJS) $(CFLAGS)

# $< is the first dependancy
bakery.o : bakery.cpp $(DEPS) $(OBJS)
	$(CC) -c $< $(CFLAGS)

Money.o : Money.cpp $(DEPS)
	$(CC) -c $<

Day.o : Day.cpp $(DEPS)
	$(CC) -c $<

CashRegister.o : CashRegister.cpp $(DEPS)
	$(CC) -c $<

Item.o : Item.cpp $(DEPS)
	$(CC) -c $<

CreditCard.o : CreditCard.cpp $(DEPS)
	$(CC) -c $<


# rules for administrator program
admin : admin.o $(ADMIN_DEPS) $(ADMIN_OBJS)
	$(CC) -o admin $< $(ADMIN_OBJS)	

Password.o : Password.cpp $(ADMIN_DEPS)
	$(CC) -c $<

admin.o : admin.cpp $(ADMIN_DEPS) $(ADMIN_OBJS)
	$(CC) -c $<


clean : 
	rm *.o *.out *.bin bakery admin
