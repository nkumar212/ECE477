target : image_gen

image_gen : image_gen.c
	gcc -Wall -I./libfreenect/include -I/usr/include/libusb-1.0 -Ilibfreenect/wrappers/c_sync image_gen.c -o image_gen -lfreenect -ljpeg -lm
