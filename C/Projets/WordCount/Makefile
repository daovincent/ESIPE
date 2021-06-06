CC=gcc
CFLAGS=-Wall -ansi
LDFLAGS=-lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

wordcount: wordcount.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) wordcount
