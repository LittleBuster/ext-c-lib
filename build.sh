#!/bin/bash

#Platform WIN32 or UNIX

PLATFORM=UNIX

#Included moduls

TCPSOCKET=true
SLIST=true
DLIST=true
JSONCONF=true
TIMER=true


CFLAGS=" -O2 -Wall -Wno-pointer-arith -I. -pedantic -std=gnu99"
OUT="gcc"


if [[ $TCPSOCKET == true ]]; then
	PIC=""
	if [[ $PLATFORM == UNIX ]]; then
		PIC=" -fPIC"
	fi

	STR="gcc tcpsocket.c -c $CFLAGS $PIC -lpthread"
	echo $STR
	$STR

	OUT+=" tcpsocket.o -lpthread"
fi


if [[ $SLIST == true ]]; then
	PIC=""
	if [[ $PLATFORM == UNIX ]]; then
		PIC=" -fPIC"
	fi

	STR="gcc slist.c -c $CFLAGS $PIC"
	echo $STR
	$STR

	OUT+=" slist.o"
fi


if [[ $DLIST == true ]]; then
	PIC=""
	if [[ $PLATFORM == UNIX ]]; then
		PIC=" -fPIC"
	fi

	STR="gcc dlist.c -c $CFLAGS $PIC"
	echo $STR
	$STR

	OUT+=" dlist.o"
fi


if [[ $TIMER == true ]]; then
	PIC=""
	if [[ $PLATFORM == UNIX ]]; then
		PIC=" -fPIC"
	fi

	STR="gcc stimer.c -c $CFLAGS $PIC -lrt"
	echo $STR
	$STR

	OUT+=" stimer.o -lrt"
fi

if [[ $JSONCONF == true ]]; then
	PIC=""
	if [[ $PLATFORM == UNIX ]]; then
		PIC=" -fPIC"
	fi

	STR="gcc json-cfg.c -c $CFLAGS $PIC -ljansson"
	echo $STR
	$STR

	OUT+=" json-cfg.o -ljansson"
fi


if [[ $PLATFORM ==  UNIX ]]; then
	LIBNAME="libextc.so"
else
	LIBNAME="extc.dll"
fi

$OUT -shared -o $LIBNAME $CFLAGS
echo $OUT -shared -o $LIBNAME $CFLAGS
