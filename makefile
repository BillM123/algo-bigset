CC=clang
CFLAGS=-Wall -g

main: main.o graph-functions.o fifo.o
	$(CC) $(CFLAGS) -o $@ $^ -fsanitize=address

main.o: main.c datatypes.h prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $<

graph-functions.o: graph-functions.c datatypes.h prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $<

fifo.o: fifo.c datatypes.h prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm main main.o graph-functions.o fifo.o