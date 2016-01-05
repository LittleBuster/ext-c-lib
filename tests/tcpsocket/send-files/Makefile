CC=gcc
CFLAGS=-Wall -I. -std=gnu99
LDFLAGS=-lpthread -lextc


all:
	$(CC) server.c filetransfer.c -o server $(CFLAGS) $(LDFLAGS)
	$(CC) client.c filetransfer.c -o client $(CFLAGS) $(LDFLAGS)

clean:
	-rm server
	-rm client
