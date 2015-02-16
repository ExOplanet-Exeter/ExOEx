# Use the GNU C compiler                                                                                                                    
CC = gcc-4.9.2

# Flags                                                                                                                                     
CFLAGS = -std=c11 -g -fopenmp

# Short for working directory                                                                                                               
$(shell basename $(WKDIR))

all:arc clean


# Main build                                                                                                                                
arc: main.o
	$(CC) $(CFLAGS) main.o -o ../arc

main.o: $(WKDIR)main.c
	$(CC) $(CFLAGS) -c $(WKDIR)main.c

input.o: $(WKDIR)modules/functions/input.c
	$(CC) $(CFLAGS) -c $(WKDIR)modules/functions/input.c

photonLoop.o: $(WKDIR)modules/functions/photonLoop.c
	$(CC) $(CFLAGS) -c $(WKDIR)modules/functions/photonLoop.c

output.o: $(WKDIR)modules/functions/output.c
	$(CC) $(CFLAGS) -c $(WKDIR)modules/functions/output.c

utilities.o: $(WKDIR)globals/functions/utilities.c
	$(CC) $(CFLAGS) -c $(WKDIR)globals/functions/utilities.c

extraction.o: $(WKDIR)modules/functions/extraction.c
	$(CC) $(CFLAGS) -c $(WKDIR)modules/functions/extraction.c

gnuplot_i.o: $(WKDIR)globals/functions/gnuplot_i.c
	$(CC) $(CFLAGS) -c $(WKDIR)globals/functions/gnuplot_i.c


# Clean up                                                                                                                                  
.PHONY: clean

clean:
	rm -f $@ $(WKDIR)*.o $(WKDIR)*~ $(WKDIR)*#
	rm -f $@ $(WKDIR)dependencies/*.o $(WKDIR)dependencies/*~ $(WKDIR)dependencies/*#
	rm -f $@ $(WKDIR)globals/*.o $(WKDIR)globals/*~ $(WKDIR)globals/*#
	rm -f $@ $(WKDIR)modules/*.o $(WKDIR)modules/*~ $(WKDIR)modules/*#