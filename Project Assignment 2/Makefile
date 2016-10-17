# Creates executable
mysh : mysh.o
	gcc -o mysh mysh.o

# Compiles .c file into object code
mysh.o : mysh.c
	gcc -c mysh.c

# Removes all object files
clean :
	rm *.o
