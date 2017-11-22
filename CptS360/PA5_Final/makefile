
CC=gcc
CFLAGS=-g -Wall -Wstrict-prototypes

default: tattled rtattle

tattled: 
	$(CC) $(CFLAGS) -o tattled tattled.c daemonize_me.c

rtattle: 
	$(CC) $(CFLAGS) -o rtattle rtattle.c get_sockaddr.c


clean:
	-rm tattled
	-rm rtattle
