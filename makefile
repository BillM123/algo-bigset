CC=gcc
CFLAGS=-Wall -g

main: main.o graph-functions.o fifo.o cpl_sp.o
	$(CC) $(CFLAGS) -O3 -fopenmp -o $@ $^
	@echo -e "\nTo test the program, try running \033[1;34mmake \033[0;37mtest\033[0m"
main.o: main.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -O3 -c -o $@ $< 
graph-functions.o: dependencies/graph-functions.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -O3 -c -o $@ $< 
cpl_sp.o: dependencies/cpl_sp.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -O3 -c -fopenmp -o $@ $<
fifo.o: dependencies/fifo.c dependencies/include/datatypes.h dependencies/include/prototypes.h
	$(CC) $(CFLAGS) -O3 -c -o $@ $< 
format: dependencies/format.c
	$(CC) $(CFLAGS) -o $@ $<

test: main edgelists/karate-formatted.edgelist edgelists/grid-formatted.edgelist edgelists/Erdos-formatted.edgelist
	@echo -e "\n\033[1;33mNote: \033[0mFor any custom test, try formatting it with the command:"
	@echo -e "\033[1;34mformat \033[0;33m\"path/to/edgelist\" \"path/to/output\" \033[0;37mNumberOfVertices \033[0m"
	@echo -e "or by changing the file so the numberOfvertices is in line 1, \"end\" on the\nfinal line, and the vertcices in each line are separated by a space"
	@make test1
	@make test2
	@make test3
edgelists/karate-formatted.edgelist: edgelists/karate.edgelist format
	./format edgelists/karate.edgelist edgelists/karate-formatted.edgelist
edgelists/grid-formatted.edgelist: edgelists/grid.edgelist format
	./format edgelists/grid.edgelist edgelists/grid-formatted.edgelist
edgelists/Erdos-formatted.edgelist: edgelists/Erdos.edgelist
	./format edgelists/Erdos.edgelist edgelists/Erdos-formatted.edgelist

test1: main edgelists/karate-formatted.edgelist
	@echo -e "\n\033[1;33mStarting test 1...\033[0m"
	time ./main edgelists/karate-formatted.edgelist > output/karate.out
test2: main edgelists/grid-formatted.edgelist
	@echo -e "\n\033[1;33mStarting test 2...\033[0m"
	time ./main edgelists/grid-formatted.edgelist > output/grid.out
test3: main	edgelists/Erdos-formatted.edgelist
	@echo -e "\n\033[1;33mStarting test 3...\033[0m"
	time ./main edgelists/Erdos-formatted.edgelist > output/Erdos.out

.PHONY:

clean:
	@rm main main.o graph-functions.o fifo.o cpl_sp.o
clean_format:
	@rm format
