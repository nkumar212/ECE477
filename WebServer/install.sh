#!/bin/bash

#Use this script to install the WebSockets module within python
#You can then run the script manually with ./cnc.py or you can
#Use the full run.sh version which will also launch an instance
#Of ffserver and awaits connections from a minotaur robot.

apt-get install python-dev python-setuptools vlc libav-tools libavcodec-extra-53 libavcodec-53 --yes
cd txws/txWS-master
python setup.py install && echo 'Completed successfully'
