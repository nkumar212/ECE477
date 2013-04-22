#!/bin/bash

#sudo apt-get install git-core cmake libglut3-dev pkg-config build-essential libxmu-dev libxi-dev libusb-1.0-0-dev
sudo apt-get install git-core cmake freeglut3-dev pkg-config build-essential libxmu-dev libxi-dev libusb-1.0-0-dev libfftw3-{3,dev} --yes
git clone git://github.com/OpenKinect/libfreenect.git
cd libfreenect
mkdir build
cd build
cmake ..
make -j 4
sudo make install
sudo ldconfig /usr/local/lib64/
cd ../..
make clean
rm -f ids
make -j 4
