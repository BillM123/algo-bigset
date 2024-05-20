CC=clang
CFLAGS=-Wall -g

main: main.o graph-functions.o fifo.o cpl_sp.o
	$(CC) $(CFLAGS) -o $@ $^ -fsanitize=address
main.o: main.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $< -fsanitize=address
graph-functions.o: dependencies/graph-functions.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $< -fsanitize=address
cpl_sp.o: dependencies/cpl_sp.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $< -fsanitize=address
fifo.o: dependencies/fifo.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -c -o $@ $< -fsanitize=address
format: format.c
	$(CC) $(CFLAGS) -o $@ $<

test: main edgelists/karate-formatted.edgelist edgelists/grid-formatted.edgelist edgelists/Erdos-formatted.edgelist
	./main edgelists/karate-formatted.edgelist >> output/karate.out
	./main edgelists/grid-formatted.edgelist >> output/grid.out
	./main edgelists/Erdos-formatted.edgelist >> output/Erdos.out
edgelists/karate-formatted.edgelist: edgelists/karate.edgelist format
	./format edgelists/karate.edgelist edgelists/karate-formatted.edgelist
edgelists/grid-formatted.edgelist: edgelists/grid.edgelist format
	./format edgelists/grid.edgelist edgelists/grid-formatted.edgelist
edgelists/Erdos-formatted.edgelist: edgelists/Erdos.edgelist
	./format edgelists/Erdos.edgelist edgelists/Erdos-formatted.edgelist



.PHONY:
exec: main
	./main edgelists/$(EDGELIST)-formatted.edgelist
clean:
	@rm main main.o graph-functions.o fifo.o cpl_sp.o
