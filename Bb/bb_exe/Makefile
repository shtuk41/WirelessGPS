CC=gcc
CFLAGS=-c -Wall

all:	bb

bb: bb.o bb_server.o bb_process_gps_inputs.o
	$(CC) bb.o bb_server.o bb_process_gps_inputs.o -o bb

bb.o:	bb.c 
	$(CC) $(CFLAGS) bb.c

bb_server.o:	bb_server.c
	$(CC) $(CFLAGS) bb_server.c

bb_process_gps_inputs.o:	bb_process_gps_inputs.c
	$(CC) $(CFLAGS) bb_process_gps_inputs.c

clean:
	rm -rf *o bb *~

cleanextra:
	rm -rf *o *~
