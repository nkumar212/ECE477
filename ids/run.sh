#!/bin/bash

#FFServer Host as $1
HOST="$1"

if [[ -z "$HOST" ]] ; then
	HOST="zeus-cnc.no-ip.info"
fi

sudo chmod a+rw /dev/ttyS0

cd `dirname "$0"`

mkdir -p logs

if [[ -z "$USER" ]] ; then
	USER=`whoami`
fi

if [[ "$USER" != "root" ]] ; then
	echo "You must be root to run this script"
	exit 1
fi

if [[ "$HOST" == "localhost" ]] ; then
	pkill avserver
	rm -rf /tmp/feed1.ffm
	avserver -f ./ffserver.conf > logs/avserver_stdout.log 2> logs/avserver_stderr.log &
fi;

#valgrind --tool=callgrind ./ids > /dev/null
./ids $HOST | avconv -f rawvideo -s 320x240 -pix_fmt yuv420p -i - -r 24 http://$HOST:8090/feed1.ffm >/dev/null 2>/dev/null
#./ids 2>logs/ids_stderr.log | avconv -f rawvideo -s 320x240 -pix_fmt yuv420p -i - -r 24 -f mjpeg test.mjpeg
