# Use the GNU C compiler.
CC = gcc-4.9.2

# Flags.
CFLAGS = -std=c11 -g -fopenmp

# Shortcut for working directory.
$(shell basename $(WKDIR))


# Routines to execute.
all: test clean


# Main build: 'test'.
test: main.o
	$(CC) $(CFLAGS) main.o -o test
	
main.o: $(WKDIR)main.c
	$(CC) $(CFLAGS) -c $(WKDIR)main.c
	
utilities.o: $(WKDIR)../Arc/globals/utilities.c
	$(CC) $(CFLAGS) -c $(WKDIR)../Arc/globals/utilities.c	
	
	
# Clean up commands.
.PHONY: clean

clean:
	rm -f $@ $(WKDIR)*~ $(WKDIR)*.o
	rm -f $@ $(WKDIR)../modules/*~ $(WKDIR)../modules/*.o