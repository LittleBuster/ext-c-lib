CC=gcc
CFLAGS=-O3 -Wall -I. -std=gnu99
LDFLAGS=-lpthread


all: extc_net

extc_net: extc_tcpsocket.o
	$(CC) extc_tcpsocket.o -shared -o libextc_net.so $(CFLAGS) $(LDFLAGS)

extc_tcpsocket.o: extc_tcpsocket.c
	$(CC) extc_tcpsocket.c -c $(CFLAGS) $(LDFLAGS) -fPIC

install:
	-sudo mkdir /usr/include/extc
	sudo cp *.h /usr/include/extc/
	sudo cp libextc_net.so /usr/lib/
	-sudo cp libextc_net.so /usr/lib64/

remove:
	sudo rm /usr/include/extc/extc_net.h
	sudo rm /usr/include/extc/extc_tcpsocket.h
	sudo rm /usr/lib/libextc_net.so
	-sudo rm /usr/lib64/libextc_net.so

clean:
	rm -rf libextc_net.so *.o
