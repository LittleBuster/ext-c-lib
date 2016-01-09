#!/bin/bash

#Included moduls

TCPSOCKET=true
SLIST=true
DLIST=true
JSONCONF=true
TIMER=true


if [[ $@ == "clean" ]]; then
    rm -rf *.o
    rm extc.dll
    echo "Temporary files cleared"
    exit 0
fi

if [[ $@ == "install" ]]; then
    mkdir /usr/include/extc/
    cp *.h /usr/include/extc/
    cp extc.dll /usr/lib/

    echo "Files installed"
    exit 0
fi

if [[ $@ == "remove" ]]; then
    rm -rf /usr/include/extc/
    rm /usr/lib/extc.dll

    echo "Files removed."
    exit 0
fi


CFLAGS=" -O2 -Wall -Wno-pointer-arith -I. -pedantic -std=gnu99"
OUT="gcc"


if [[ $TCPSOCKET == true ]]; then
    STR="gcc tcpsocket.c -c $CFLAGS -lpthread"
    echo $STR
    $STR

    OUT+=" tcpsocket.o -lpthread"
fi


if [[ $SLIST == true ]]; then
    STR="gcc slist.c -c $CFLAGS $PIC"
    echo $STR
    $STR

    OUT+=" slist.o"
fi


if [[ $DLIST == true ]]; then
    STR="gcc dlist.c -c $CFLAGS $PIC"
    echo $STR
    $STR

    OUT+=" dlist.o"
fi


if [[ $TIMER == true ]]; then
    STR="gcc stimer.c -c $CFLAGS $PIC -lrt"
    echo $STR
    $STR

    OUT+=" stimer.o -lrt"
fi

if [[ $JSONCONF == true ]]; then
    STR="gcc json-cfg.c -c $CFLAGS $PIC -ljansson"
    echo $STR
    $STR

    OUT+=" json-cfg.o -ljansson"
fi

$OUT -shared -o extc.dll $LIBNAME $CFLAGS
echo $OUT -shared -o extc.dll $LIBNAME $CFLAGS
