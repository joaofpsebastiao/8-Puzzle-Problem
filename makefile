CC=gcc
CFLAGS=-Wall 
DEPS=headers.h algorithms.h list.h game.h
OBJ=main.o algorithms.o list.o game.o 

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

homework1: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	rm *.o homework1
