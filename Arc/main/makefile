# Use the GNU C compiler.
CC = gcc
#edited from gcc-4.9.2 to gcc

# Flags.
CFLAGS = -std=c11 -g -fopenmp

# Shortcut for working directory.
$(shell basename $(WKDIR))


# Routines to execute.
all: arc clean


# Main build: 'arc'.
arc: main.o input.o photonLoop.o extraction.o reduction.o output.o utilities.o testing.o gnuplot_i.o
	$(CC) $(CFLAGS) main.o input.o photonLoop.o extraction.o reduction.o output.o utilities.o testing.o gnuplot_i.o -o arc
	
main.o: $(WKDIR)main.o
	$(CC) $(CFLAGS) -c $(WKDIR)main.c
	
input.o: $(WKDIR)../modules/input.o
	$(CC) $(CFLAGS) -c $(WKDIR)../modules/input.c
	
photonLoop.o: $(WKDIR)../modules/photonLoop.o
	$(CC) $(CFLAGS) -c $(WKDIR)../modules/photonLoop.c
	
extraction.o: $(WKDIR)../modules/extraction.o
	$(CC) $(CFLAGS) -c $(WKDIR)../modules/extraction.c
	
reduction.o: $(WKDIR)../modules/reduction.o
	$(CC) $(CFLAGS) -c $(WKDIR)../modules/reduction.c
	
output.o: $(WKDIR)../modules/output.o
	$(CC) $(CFLAGS) -c $(WKDIR)../modules/output.c
	
utilities.o: $(WKDIR)../globals/utilities.o
	$(CC) $(CFLAGS) -c $(WKDIR)../globals/utilities.c
	
testing.o: $(WKDIR)../modules/testing.o
	$(CC) $(CFLAGS) -c $(WKDIR)../modules/testing.c
	
gnuplot_i.o: $(WKDIR)../globals/gnuplot_i.o
	$(CC) $(CFLAGS) -c $(WKDIR)../globals/gnuplot_i.c
	
	
# Clean up commands.
.PHONY: clean

clean:
	rm -f $@ $(WKDIR)*~ $(WKDIR)*.o
	rm -f $@ $(WKDIR)../modules/*~ $(WKDIR)../modules/*.o