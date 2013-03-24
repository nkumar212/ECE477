To start an FFServer on a webserver:
sudo rm -f /tmp/feed1.ffm ; sudo avserver -f /etc/ffserver.conf

FFServer settings are stored in ffserver.conf

To start streaming from a kinnect:
sudo ./image_gen  | avconv -f rawvideo -s 320x240 -pix_fmt yuv420p -i - -r 20 -s 320x240 http://localhost:8090/feed1.ffm

To start saving video from the kinnect to a .mpg file
rm test.mpg ; sudo ./image_gen  | avconv -f rawvideo -s 320x240 -pix_fmt yuv420p -i - -r 20 -s 320x240 test.mpg
