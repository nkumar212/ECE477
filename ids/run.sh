#!/bin/bash

#FFServer Host as $1
HOST="$1"

if [[ -z "$HOST" ]] ; then
	HOST="zeus-cnc.no-ip.info"
fi

sudo chmod a+rw /dev/ttyUSB0

cd `dirname "$0"`

mkdir -p logs

if [[ -z "$USER" ]] ; then
	USER=`whoami`
fi

if [[ "$USER" != "root" ]] ; then
	echo "You must be root to run this script"
	exit 1
fi

set -o verbose

if [[ "$HOST" == "localhost" ]] ; then
	pkill avserver
	pkill cnc.py
	for pid in `ps aux | grep cnc.py | grep -v grep | perl -pe 's/\s+/\t/g'| cut -f 2` ; do
		kill -9 "$pid"
	done
	sleep 1
	cd ../WebServer
	./run.sh 2>&1 > /dev/null &
	sleep 2
	cd ../ids
fi;

#valgrind --tool=callgrind ./ids > /dev/null
./ids $HOST 2> test.txt | avconv -f rawvideo -s 320x240 -pix_fmt yuv420p -i - -r 24 http://$HOST:8090/feed1.ffm >/dev/null 2>/dev/null
#./ids 2>logs/ids_stderr.log | avconv -f rawvideo -s 320x240 -pix_fmt yuv420p -i - -r 24 -f mjpeg test.mjpeg
