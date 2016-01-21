CC=gcc
CFLAGS=-Wall -I. -std=gnu99
LDFLAGS=-lextc


all:
	$(CC) server.c filetransfer.c -o server $(CFLAGS) $(LDFLAGS)
	$(CC) client.c filetransfer.c -o client $(CFLAGS) $(LDFLAGS)

clean:
	-rm server
	-rm client
	-rm -rf out
