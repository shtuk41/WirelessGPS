

CC=gcc
CFLAGS=-c -Wall -ggdb

all:  	nmeamain

nmeamain:	nmeamain.o nmeamain.c nmea.o mtk_nmea.o circular_buffer.o
	$(CC) 	-o nmeamain	-ggdb nmeamain.c nmea.o mtk_nmea.o circular_buffer.o

nmea.o: 	nmea.c
	$(CC) 	$(CFLAGS) nmea.c
	
mtk_nmea.o:	mtk_nmea.c
	$(CC)	$(CFLAGS) mtk_nmea.c

circular_buffer.o:	circular_buffer.c
	$(CC) $(CFLAGS) circular_buffer.c

clean:	
	rm -rf *o nmeamain a.out *.exe *# *~

	
