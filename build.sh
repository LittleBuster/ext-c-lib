#!/bin/bash

#Platform WIN32 or UNIX

PLATFORM=WIN32

#Included moduls

TCPSOCKET=true
SLIST=true
DLIST=true
JSONCONF=true
TIMER=true


if [[ $@ == "clean" ]]; then
    rm -rf *.o
    if [[ $PLATFORM == UNIX ]]; then
        rm libextc.so
    else
        rm extc.dll
    fi
    echo "Temporary files cleared"
    exit 0
fi

if [[ $@ == "install" ]]; then
    if [[ $PLATFORM == UNIX ]]; then
        sudo mkdir /usr/include/extc/
        sudo cp *.h /usr/include/extc/
        sudo cp libextc.so /usr/lib/
        sudo cp libextc.so /usr/lib64/
    else
        mkdir /usr/include/extc/
        cp *.h /usr/include/extc/
        cp extc.dll /usr/lib/
    fi
    echo "Files installed"
    exit 0
fi

if [[ $@ == "remove" ]]; then
    if [[ $PLATFORM == UNIX ]]; then
        sudo rm /usr/lib/libextc.so
        sudo rm /usr/lib64/libextc.so
        sudo rm -rf /usr/include/extc/
    else
        rm -rf /usr/include/extc/
        rm /usr/lib/extc.dll
    fi
    echo "Files removed."
    exit 0
fi


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
