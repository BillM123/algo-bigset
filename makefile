CC=clang
CFLAGS=-Wall -g

main: main.o graph-functions.o fifo.o
	$(CC) $(CFLAGS) -D=$(EDGELIST) -o $@ $^ -fsanitize=address
main.o: main.c include/datatypes.h include/prototypes.h
	$(CC) $(CFLAGS) -D=$(EDGELIST) -c -o $@ $<
graph-functions.o: graph-functions.c include/datatypes.h include/prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $<
fifo.o: fifo.c include/datatypes.h include/prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $<
format: format.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:
exec: main
	@./main edgelists/$(EDGELIST).edgelist
clean:
	@rm main main.o graph-functions.o fifo.o