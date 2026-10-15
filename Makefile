CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

chipsim: main.o pc.o, ram8.o
	$(CC) $(CFLAGS) main.o pc.o ram8.0 -o chipsim

main.o: main.c pc.h ram8.c
	$(CC) $(CFLAGS) -c main.c

pc.o: pc.c pc.h
	$(CC) $(CFLAGS) -c pc.c

ram8.o: ram8.c ram8.h
   $(CC) $(CFLAGS) -c ram8.c	

.PHONY: clean
clean:
	rm -f chipsim main.o pc.o
