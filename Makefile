CC=gcc
CFLAGS=-O3 -Wall -I. -std=gnu99
LDFLAGS=-lpthread


all: extc

extc: tcpsocket.o
	$(CC) tcpsocket.o -shared -o libextc.so $(CFLAGS) $(LDFLAGS)

tcpsocket.o: tcpsocket.c
	$(CC) tcpsocket.c -c $(CFLAGS) $(LDFLAGS) -fPIC

install:
	-sudo mkdir /usr/include/extc
	sudo cp *.h /usr/include/extc/
	sudo cp libextc.so /usr/lib/
	-sudo cp libextc.so /usr/lib64/

remove:
	sudo rm -rf /usr/include/extc/
	sudo rm /usr/lib/libextc.so
	-sudo rm /usr/lib64/libextc.so

clean:
	rm -rf libextc.so *.o
