CC=gcc
CFLAGS=-Wall -I. -std=gnu99
LDFLAGS=-lpthread


all:
	$(CC) server.c -lextc -o server $(LDFLAGS)
	$(CC) client.c -lextc -o client $(LDFLAGS)

clean:
	rm server client
