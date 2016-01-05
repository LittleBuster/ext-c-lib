#!/bin/bash

#Platform UNIX or WIN32

PLATFORM=UNIX

rm *.o

if [[ $PLATFORM == UNIX ]]; then
	rm libextc.so
else
	rm extc.dll
fi

echo "All files cleaned."
