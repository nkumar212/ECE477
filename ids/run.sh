#!/bin/bash

#FFServer Host as $1
HOST="$1"

sudo chmod a+rw /dev/ttyUSB0

if [[ "$USER" != "root" ]] ; then
	echo "You must be root to run this script"
	exit 1
fi

if [[ "$HOST" == "localhost" ]] ; then
	pkill avserver
	rm -rf /tmp/feed1.ffm
	avserver -f ./ffserver.conf > logs/avserver_stdout.log 2> logs/avserver_stderr.log &
	sleep 3
fi;

#./ids 2>logs/ids_stderr.log | avconv -f rawvideo -s 320x240 -pix_fmt yuv420p -i - -r 24 -vcodec flv -f mjpeg http://$HOST:8090/feed1.ffm
./ids 2>logs/ids_stderr.log | avconv -f rawvideo -s 320x240 -pix_fmt yuv420p -i - -r 24 -f mjpeg test.mjpeg
