CC=gcc
CFLAGS=-Wall -ansi
LDFLAGS=-lm
DEPS=msortchain.h
OBJ=msortchain.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) main
