CC=gcc
CFLAGS=-c -Wall

all:	BBprocess

BBprocess: BBprocess.o
	 $(CC) BBprocess.o -o BBprocess

BBprocess.o:	BBprocess.c
	$(CC) $(CFLAGS) BBprocess.c

clean:
	rm -rf *o BBprocess *~

cleanextra:
	rm -rf *o *~
