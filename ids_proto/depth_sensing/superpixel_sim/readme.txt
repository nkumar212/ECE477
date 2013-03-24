#Running slope field/depth simulation.  You have to provide a location for the
#bitmap header, an input depth dump, and a size for the output superpixel
#this program runs significantly slower at 8 than 4 because the python script
#does not make any attempt to re-use averaging data.  Once we calculate the data
#just once per superpixel the speed increase should be nearly directly 
#proportional to the size of the superpixel.

./depth.py bmp_header_640x480 frame.dump 8 > frame.c8.bmp
