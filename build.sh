#!/bin/bash

#Platform WIN32 or UNIX

PLATFORM=UNIX

#Included moduls

TCPSOCKET=true
SLIST=true
DLIST=true
JSONCONF=true
TIMER=true
GETTIME=true

CC="gcc"

#Params flags
P=false
M=false
C=false
ISPARAMS=false
ISPF=false


if [[ $@ == "" ]]; then
    echo "[ERROR] Parameters not found!"
    exit 1
fi


for param in $@
do
    if [[ $P == true ]]; then
        if [[ $param == "win32" ]]; then
            PLATFORM=WIN32
        fi
        if [[ $param == "unix" ]]; then
            PLATFORM=UNIX
        fi
        ISPF=true
        P=false
        echo "Target platform: $PLATFORM"
        continue
    fi

    if [[ $M == true ]]; then
        if [[ $param == "all" ]]; then
            M=false
            continue
        fi

        TCPSOCKET=false
        SLIST=false
        DLIST=false
        JSONCONF=false
        TIMER=false
        GETTIME=false

        ISPARAMS=true
        echo "Building modules..."
        echo ""

        while IFS=',' read -ra ADDR; do
            for i in "${ADDR[@]}"; do
                case $i in
                    tcp )
                        TCPSOCKET=true
                        echo "[M] TcpSocket"
                        ;;
                    tmr )
                        TIMER=true
                        echo "[M] Timer"
                        ;;
                    slist )
                        SLIST=true
                        echo "[M] SingleList"
                        ;;
                    dlist )
                        DLIST=true
                        echo "[M] DoubleList"
                        ;;
                    jcfg )
                        JSONCONF=true
                        echo "[M] JsonConfigs"
                        ;;
                    gtime )
                        GETTIME=true
                        echo "[M] GetTime"
                        ;;
                esac
            done
        done <<< "$param"
        M=false
        echo ""
        continue
    fi

    if [[ $C == true ]]; then
        CC=$param
        C=false
        continue
    fi

    if [[ $param == "-p" ]]; then
        P=true
        continue
    fi

    if [[ $param == "-m" ]]; then
        M=true
        continue
    fi

    if [[ $param == "-c" ]]; then
        C=true
        continue
    fi

    #Extended scripts
    if [[ $param == "clean" ]]; then
        rm -rf *.o
        if [[ $PLATFORM == UNIX ]]; then
            rm libextc.so
        else
            rm extc.dll
        fi
        echo "Temporary files cleaned"
        exit 0
    fi

    if [[ $param == "install" ]]; then
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

    if [[ $param == "remove" ]]; then
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
done

if [[ $ISPF == false ]]; then
    echo "Target default platform: $PLATFORM"
fi

if [[ $ISPARAMS == false ]]; then
    echo "Building modules..."
    echo ""
    echo "[M] TcpSocket"
    echo "[M] Timer"
    echo "[M] SingleList"
    echo "[M] DoubleList"
    echo "[M] JsonConfigs"
    echo "[M] GetTime"
    echo ""
fi


CFLAGS=" -O2 -Wall -Wno-pointer-arith -I. -std=gnu99"
OUT=$CC


func_compile() {
    if [[ $1 == true ]]; then
        PIC=""
        if [[ $PLATFORM == UNIX ]]; then
            PIC=" -fPIC"
        fi

        echo $CC $2 $PIC $CFLAGS
        $CC $2 $PIC $CFLAGS

        OUT+=$3
    fi
    return 0
}

func_compile $TCPSOCKET  " tcpsocket.c -c -lpthread" " tcpsocket.o -lpthread"
func_compile $SLIST  " slist.c -c" " slist.o"
func_compile $DLIST  " dlist.c -c" " dlist.o"
func_compile $TIMER " stimer.c -c -lrt" " stimer.o -lrt"
func_compile $JSONCONF " json-cfg.c -c -ljansson" " json-cfg.o -ljansson"
func_compile $GETTIME " gettime.c -c" " gettime.o"


if [[ $PLATFORM ==  UNIX ]]; then
    LIBNAME="libextc.so"
else
    LIBNAME="extc.dll"
fi

$OUT -shared -o $LIBNAME $CFLAGS
echo $OUT -shared -o $LIBNAME $CFLAGS

echo
echo "Complete."
