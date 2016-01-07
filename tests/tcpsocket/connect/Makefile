CC=gcc
CFLAGS=-Wall -I. -std=gnu99
LDFLAGS=-lextc


all:
	$(CC) server.c -o server $(CFLAGS) $(LDFLAGS)
	$(CC) client.c -o client $(CFLAGS) $(LDFLAGS)

clean:
	rm server client
