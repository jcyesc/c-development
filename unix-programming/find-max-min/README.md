
############################################################################################
#
# FIND THE MAXIMUM AND MINIMUM
# 
# This project implement the programs to find the maximum and minimum in three ways:
#
#	Sequential		It findes the maximum and minimum sequentially.
#	Parallel		It uses files and forks to find the maximum and minimum.
#	Pipes			It uses pipes to find the maximum and minimum
#
############################################################################################

Files:
    util.h					It contains the signature of utility functions used across the application
    util.c					It contains the implementation of the utility functions
    measure.h				It contains the function to measure execution times
	findminmax_parallel.c	It contains the parallel program.
	findminmax_sequential.c It contains the sequential program
	findminmax_pipes.c		It contains the pipes program
	makefile				It contains the make tasks.
	

	
	
############################################################################################
#
# HOW TO EXECUTE THE CODE
#
# There is a makefile that contains the different tasks to compile and execute each program. On
# top of the file there are three tasks  and two of then are commented:
#
#		all: runSequential
#		all: runParallel
#		all: runPipes
#
# In order to execute a program in particular, just uncomment the task and comment the 
# previous uncommented task.
# 
# In addition to this, you can also configure the different parameters of the program
# in execution.
#
# 		Example:
#			./findminmax_sequential 1 400000000
#
############################################################################################



