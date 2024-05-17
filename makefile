CC=clang
CFLAGS=-Wall -g

main: main.o graph-functions.o fifo.o cpl_sp.o
	$(CC) $(CFLAGS) -D=$(EDGELIST) -o $@ $^ -fsanitize=address
main.o: main.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -D=$(EDGELIST) -c -o $@ $<
graph-functions.o: dependencies/graph-functions.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $<
fifo.o: dependencies/fifo.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $<
cpl_sp.o: dependencies/cpl_sp.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $<


.PHONY:
exec: main
	@./main edgelists/$(EDGELIST).edgelist
clean:
	@rm main main.o graph-functions.o fifo.o cpl_sp.o