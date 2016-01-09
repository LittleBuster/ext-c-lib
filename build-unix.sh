#!/bin/bash

#Included moduls

TCPSOCKET=true
SLIST=true
DLIST=true
JSONCONF=true
TIMER=true


if [[ $@ == "clean" ]]; then
    rm *.o
    rm libextc.so

    echo "Temporary files cleared"
    exit 0
fi

if [[ $@ == "install" ]]; then
    sudo mkdir /usr/include/extc/
    sudo cp *.h /usr/include/extc/
    sudo cp libextc.so /usr/lib/
    sudo cp libextc.so /usr/lib64/

    echo "Files installed"
    exit 0
fi

if [[ $@ == "remove" ]]; then
    sudo rm /usr/lib/libextc.so
    sudo rm /usr/lib64/libextc.so
    sudo rm -rf /usr/include/extc/

    echo "Files removed."
    exit 0
fi


CFLAGS=" -O2 -Wall -Wno-pointer-arith -I. -pedantic -std=gnu99"
OUT="gcc"


if [[ $TCPSOCKET == true ]]; then
    STR="gcc tcpsocket.c -c $CFLAGS -fPIC -lpthread"
    echo $STR
    $STR

    OUT+=" tcpsocket.o -lpthread"
fi


if [[ $SLIST == true ]]; then
    STR="gcc slist.c -c $CFLAGS -fPIC"
    echo $STR
    $STR

    OUT+=" slist.o"
fi


if [[ $DLIST == true ]]; then
    STR="gcc dlist.c -c $CFLAGS -fPIC"
    echo $STR
    $STR

    OUT+=" dlist.o"
fi


if [[ $TIMER == true ]]; then
    STR="gcc stimer.c -c $CFLAGS -fPIC -lrt"
    echo $STR
    $STR

    OUT+=" stimer.o -lrt"
fi

if [[ $JSONCONF == true ]]; then
    STR="gcc json-cfg.c -c $CFLAGS -fPIC -ljansson"
    echo $STR
    $STR

    OUT+=" json-cfg.o -ljansson"
fi

$OUT -shared -o libextc.so $LIBNAME $CFLAGS
echo $OUT -shared -o libextc.so $LIBNAME $CFLAGS
