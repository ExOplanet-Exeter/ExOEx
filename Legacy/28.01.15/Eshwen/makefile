# This is Eshwen's testing makefile.
# Use 'make' command to compile.
# Run compiled programme with './esh'
# USE TAB NOT 4 SPACES WHEN REQUIRED!


# Use the GNU C compiler.
cc = gcc

# Flags.
CFLAGS = -g

# Shortcut for working directory.
$(shell basename $(WKDIR))


# Compile instructions.
all: esh clean


# Eshwen's test build.
esh: main.o
	$(CC) $(CFLAGS) main.o -o esh

main.o: $(WKDIR)main.c $(WKDIR)../Arc/globals/global.h $(WKDIR)eshsFuncs.h
	$(CC) $(CFLAGS) -c $(WKDIR)main.c


# Clean up.
.PHONY: clean

clean:
	rm -f $@ $(WKDIR)*.o $(WKDIR)*~ $(WKDIR)*#