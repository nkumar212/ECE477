#!/bin/bash

#Create a ramdisk to store the video data more efficiently
mkdir -p /tmp/ramdisk
if [[ -z `grep /tmp/ramdisk /proc/mounts` ]] ; then
	mount -t tmpfs -o size=256M tmpfs /tmp/ramdisk
fi

#(Re)spawn avserver
pkill avserver
avserver -f ./ffserver.conf

./cnc.py

#Clean up
pkill avserver
umount /tmp/ramdisk
rmdir /tmp/ramdisk
