# Use the GNU C compiler
cc = gcc

# Flags
CFLAGS = -g

# Short for working directory
$(shell basename $(WKDIR))

all:arc clean


				#ADD THE OTHER .Os WHEN NEEDED!

# Main build
arc: main.o input.o photonLoop.o output.o
	$(CC) $(CFLAGS) main.o input.o photonLoop.o output.o -o arc

main.o: $(WKDIR)main.c
	$(CC) $(CFLAGS) -c $(WKDIR)main.c

input.o: $(WKDIR)modules/input.c
	$(CC) $(CFLAGS) -c $(WKDIR)modules/input.c

photonLoop.o: $(WKDIR)modules/photonLoop.c
	$(CC) $(CFLAGS) -c $(WKDIR)modules/photonLoop.c

output.o: $(WKDIR)modules/output.c
	$(CC) $(CFLAGS) -c $(WKDIR)modules/output.c


# Clean up
.PHONY: clean

clean:
	rm -f $@ $(WKDIR)*.o $(WKDIR)*~ $(WKDIR)*#
	rm -f $@ $(WKDIR)dependencies/*.o $(WKDIR)dependencies/*~ $(WKDIR)dependencies/*#
	rm -f $@ $(WKDIR)globals/*.o $(WKDIR)globals/*~ $(WKDIR)globals/*#
	rm -f $@ $(WKDIR)modules/*.o $(WKDIR)modules/*~ $(WKDIR)modules/*#