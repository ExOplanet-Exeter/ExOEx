# Use the GNU C compiler
cc = gcc

# Flags
CFLAGS = -g

# Short for working directory
$(shell basename $(WKDIR))

all:arc clean


# Main build
arc: main.o input.o photonLoop.o
	$(CC) $(CFLAGS) main.o input.o photonLoop.o -o arc

main.o: $(WKDIR)main.c $(WKDIR)globals/global.h $(WKDIR)modules/module.h
	$(CC) $(CFLAGS) -c $(WKDIR)main.c

input.o: $(WKDIR)modules/input.c $(WKDIR)globals/global.h
	$(CC) $(CFLAGS) -c $(WKDIR)modules/input.c

photonLoop.o: $(WKDIR)modules/photonLoop.c $(WKDIR)globals/global.h
	$(CC) $(CFLAGS) -c $(WKDIR)modules/photonLoop.c


# Clean up
.PHONY: clean

clean:
	rm -f $@ $(WKDIR)*.o $(WKDIR)*~ $(WKDIR)*#
	rm -f $@ $(WKDIR)dependencies/*.o $(WKDIR)dependencies/*~ $(WKDIR)dependencies/*#
	rm -f $@ $(WKDIR)globals/*.o $(WKDIR)globals/*~ $(WKDIR)globals/*#
	rm -f $@ $(WKDIR)modules/*.o $(WKDIR)modules/*~ $(WKDIR)modules/*#