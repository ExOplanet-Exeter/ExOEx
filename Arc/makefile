# Use the GNU C compiler                                                                                                                    
cc = gcc

# Flags                                                                                                                                     
CFLAGS = -g

# Short for working directory                                                                                                               
$(shell basename $(WKDIR))

all:arc clean


# Main build                                                                                                                                
arc: main.o input.o photonLoop.o output.o utilities.o extraction.o gnuplot_i.o
	$(CC) $(CFLAGS) main.o input.o photonLoop.o output.o utilities.o extraction.o gnuplot_i.o -o arc

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