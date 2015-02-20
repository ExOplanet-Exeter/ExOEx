# Use the GNU C compiler.
CC = gcc-4.9.2

# Flags.
CFLAGS = -std=c11 -g -fopenmp

# Shortcut for working directory.
$(shell basename $(WKDIR))


# Routines to execute.
all: arc clean


# Main build: 'arc'.
arc: main.o utilities.o
	$(CC) $(CFLAGS) main.o utilities.o -o arc
	
main.o: $(WKDIR)main.c
	$(CC) $(CFLAGS) -c $(WKDIR)main.c
	
utilities.o: $(WKDIR)../globals/utilities.c
	$(CC) $(CFLAGS) -c $(WKDIR)../globals/utilities.c	
	
	
# Clean up commands.
.PHONY: clean

clean:
	rm -f $@ *~ *.o