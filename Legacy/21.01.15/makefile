CC = gcc

CFLAGS = -g

all: arc 

# Main build
arc: main.o input.o photonLoop.o output.o gnuplot_i.o
	$(CC) $(CFLAGS) main.o input.o photonLoop.o output.o gnuplot_i.o -o arc

main.o: main.c global.h modules.h
	$(CC) $(CFLAGS) -c main.c

input.o: input.c global.h
	$(CC) $(CFLAGS) -c input.c

photonLoop.o: photonLoop.c global.h utilities.h
	$(CC) $(CFLAGS) -c photonLoop.c

output.o: output.c global.h gnuplot_i.h
	$(CC) $(CFLAGS) -c output.c

gnuplot_i.o: gnuplot_i.c gnuplot_i.h
	$(CC) $(CFLAGS) -c gnuplot_i.c


#Freddy's Testing Area
fred: fred.o
	$(CC) $(CFLAGS) fred.o -o fred

fred.o: fred.c fred.h
	$(CC) $(CFLADS) -c fred.c


#Esh's Testing Area
esh: esh.o
	$(CC) $(CFLAGS) esh.o -o esh

esh.o: esh.c esh.h
	$(CC) $(CFLAGS) -c esh.c


#Bry's Testing Area                                                           
bry: bry.o
	$(CC) $(CFLAGS) bry.o -o bry

bry.o: bry.c bry.h
	$(CC) $(CFLAGS) -c bry.c


#Cleaning things up
.PHONY: clean

clean:
	rm -f $@ *.o *~ *#