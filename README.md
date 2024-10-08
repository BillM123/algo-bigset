Disclaimer: this is a simple project created for an university assignment. This means that it is not actively maintained, and is propably not optimal for any real use case.

# algo-bigset

To run the project use the command 'make test' inside the directory
and then give as input the edgelist you wish to run the code on.

In order to clean the main directory from any object files left(if left) 
use the command 'make clean'.

Output from every graph is located inside the 'output' directory.

CPLs are extracted with a python script into '*-cpls.out' inside the output
directory (where * = {Erdos , grid ,karate})files and then used by the
MATLAB script to create the desired plots.

For the sake of the exercise it is not necessary for the whole process to
be run through ,as there are already pre-calculated results.
By running the MATLAB script you will get the plots based on this data.
However if you wish to extract the data yourself the steps to follow are
the ones mentioned above.

Also if you wish to run every graph independently the use the command
'./main edgelists/*-formatted.edgelist' where * = {Erdos , grid ,karate}

NOTE1: Erdos edgelist takes quite some time to finish, so be patient.
NOTE2: OpenMP library is required for the program to execute.

Estimated Time for graphs is:

-- Karate: 0.006 - 0.015 sec

-- Grid: 1 - 2 minutes

-- Erdos: 3 - 4 hours

Numbers may vary based on hardware 
