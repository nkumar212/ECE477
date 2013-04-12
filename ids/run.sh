#!/bin/bash

#FFServer Host as $1
HOST="$1"

if [[ "$USER" != "root" ]] ; then
	echo "You must be root to run this script"
	exit 1
fi

if [[ "$HOST" == "localhost" ]] ; then
	pkill avserver
	rm -rf /tmp/feed1.ffm
	avserver -f ./ffserver.conf > /dev/null 2>/dev/null &
	sleep 3
fi;

./ids | avconv -f rawvideo -s 320x240 -pix_fmt yuv420p -i - -r 24 http://$HOST:8090/feed1.ffm > /dev/null
