############################################################################################
# Find Min Max Parallel
#
# It compiles the files findminmax_parallel.c, measure.h.
# The executable contains the parallel program.
#
# In order to execute this makefile we run the command:
#
# make -f makeFindminmax
#
# Note: If you can to compile the program manually, execute the 
#       command below:
#
# 	gcc -o findminmax_parallel measure.h util.h util.c findminmax_parallel.c
#
#
############################################################################################

#all: runSequential
#all: runParallel
all: runPipes

runSequential: findminmaxSequential
#	./findminmax_sequential 1 40
	./findminmax_sequential 1 400000000

runParallel: findminmax
#	./findminmax_parallel 1 400000 4
	./findminmax_parallel 1 400000000 4

runPipes: findminmaxPipes
#	./findminmax_pipes 1 400000 3
	./findminmax_pipes 1 400000000 4

# Compiling the sequential findminmax program.
findminmaxSequential: util.o measure.h findminmax_sequential.c
	gcc -o findminmax_sequential util.o measure.h findminmax_sequential.c

# Compiling the findminmax program that uses files
findminmax: util.o measure.h findminmax_parallel.c
	gcc -o findminmax_parallel util.o measure.h findminmax_parallel.c

# Compiling the findminmax program that uses pipes for IPC
findminmaxPipes: util.o measure.h findminmax_pipes.c
	gcc -o findminmax_pipes util.o measure.h findminmax_pipes.c

#findmindmax: util.o measure.h main.c
#	gcc -o findminmax_parallel util.o measure.h main.c

util.o:
	gcc -c util.h util.c

# Clean the object file before executing, so the changes are visible
clean:
	rm util.o 
	rm util.h.gch
