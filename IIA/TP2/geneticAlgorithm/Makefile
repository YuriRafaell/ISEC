CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

all: coin_change

coin_change: main.o coin_change_ea.o utils.o
	$(CC) $(CFLAGS) -o coin_change main.o coin_change_ea.o utils.o $(LDFLAGS)

main.o: main.c coin_change_ea.h
	$(CC) $(CFLAGS) -c main.c

coin_change_ea.o: coin_change_ea.c coin_change_ea.h
	$(CC) $(CFLAGS) -c coin_change_ea.c

utils.o: utils.c utils.h coin_change_ea.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o coin_change