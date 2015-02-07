# This is Freddy's testing makefile.
# Use 'make' command to compile.
# Run compiled programme with './frd'
# USE TAB NOT 4 SPACES WHEN REQUIRED!


# Use the GNU C compiler.
cc = gcc

# Flags.
CFLAGS = -g

# Shortcut for working directory.
$(shell basename $(WKDIR))


# Compile instructions.
all: frd clean


# Freddy's test build.
frd: main.o gnuplot_i.o
	$(CC) $(CFLAGS) main.o gnuplot_i.o -o frd

main.o: $(WKDIR)main.c $(WKDIR)frdsFuncs.h
	$(CC) $(CFLAGS) -c $(WKDIR)main.c
	
gnuplot_i: $(WKDIR)gnuplot_i.c $(WKDIR)gnuplot_i.h
	$(CC) $(CFLAGS) -c $(WKDIR)gnuplot_i.c


# Clean up.
.PHONY: clean

clean:
	rm -f $@ $(WKDIR)*.o $(WKDIR)*~ $(WKDIR)*#