#include "kinect.h"

Kinect* Kinect::Singleton = NULL;

Kinect::Kinect()
{
	if(Singleton) throw std::runtime_error("Tried to create second instatiation of singleton class: Kinect");
	Singleton = this;
	pthread_mutex_init(&depth_lock,NULL);
	pthread_mutex_init(&video_lock,NULL);
	initFreenect();

	video_back = (video_buffer*)malloc(sizeof(video_buffer));
	video_mid = (video_buffer*)malloc(sizeof(video_buffer));
	video_front = (video_buffer*)malloc(sizeof(video_buffer));

	depth_back = (depth_buffer*)malloc(sizeof(depth_buffer));
	depth_mid = (depth_buffer*)malloc(sizeof(depth_buffer));
	depth_front = (depth_buffer*)malloc(sizeof(depth_buffer));

	yuv_front = (uint8_t*)malloc(sizeof(yuv_buffer));
	alt_video_source = NULL;
}

Kinect::~Kinect()
{
	freenect_stop_depth(f_dev);
	freenect_stop_video(f_dev);
	freenect_close_device(f_dev);
	freenect_shutdown(f_ctx);

	free(depth_back);
	free(depth_mid);
	free(depth_front);

	free(video_back);
	free(video_mid);
	free(video_front);

	free(yuv_front);
}

Kinect* Kinect::getSingleton()
{
	if(Singleton) return Singleton;
	return new Kinect();
}

void Kinect::initFreenect()
{
	int nr_devices;
	int user_device_number = 0;

	if(freenect_init(&f_ctx, NULL) < 0) {
		throw std::runtime_error("Function freenect_init() failed");
	}

	freenect_set_log_level(f_ctx, FREENECT_LOG_DEBUG);
	freenect_select_subdevices(f_ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));

	nr_devices = freenect_num_devices(f_ctx);

	if(nr_devices < 1) {
		freenect_shutdown(f_ctx);
		throw std::runtime_error("Kinect device not found");
	}

	if(freenect_open_device(f_ctx, &f_dev, user_device_number) < 0) {
		freenect_shutdown(f_ctx);
		throw std::runtime_error("Could not open Kinect");
	}

	freenect_set_tilt_degs(f_dev, -5);
	freenect_set_led(f_dev, LED_GREEN);

	freenect_set_depth_buffer(f_dev, depth_back);
	freenect_set_depth_mode(f_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_11BIT));
	freenect_set_depth_callback(f_dev, depth_cb);
	freenect_start_depth(f_dev);

	freenect_set_video_buffer(f_dev, video_back);
	freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB));
	freenect_set_video_callback(f_dev, video_cb);
	freenect_start_video(f_dev);
}

void Kinect::swapVideoBackBuffer()
{
	video_buffer* video_tmp;

	pthread_mutex_lock(&video_lock);
	video_tmp = video_back;
	video_back = video_mid;
	freenect_set_video_buffer(f_dev, video_back);
	video_mid = video_tmp;
	pthread_mutex_unlock(&video_lock);
}

void Kinect::swapVideoFrontBuffer()
{
	video_buffer* video_tmp;

	pthread_mutex_lock(&video_lock);
	video_tmp = video_front;
	video_front = video_mid;
	video_mid = video_tmp;
	pthread_mutex_unlock(&video_lock);
}

void Kinect::swapDepthBackBuffer()
{
	depth_buffer* depth_tmp = NULL;

	pthread_mutex_lock(&depth_lock);
	depth_tmp = depth_back;
	depth_back = depth_mid;
	freenect_set_depth_buffer(f_dev, depth_back);
	depth_mid = depth_tmp;
	pthread_mutex_unlock(&depth_lock);
}

void Kinect::swapDepthFrontBuffer()
{
	depth_buffer* depth_tmp = NULL;

	pthread_mutex_lock(&depth_lock);
	depth_tmp = depth_front;
	depth_front = depth_mid;
	depth_mid = depth_tmp;
	pthread_mutex_unlock(&depth_lock);
}

void Kinect::video_cb(freenect_device *dev, void *rgb, uint32_t timestamp)
{
	getSingleton()->swapVideoBackBuffer();
}

void Kinect::depth_cb(freenect_device *dev, void *rgb, uint32_t timestamp)
{
	getSingleton()->swapDepthBackBuffer();
}

Kinect::video_buffer* Kinect::getVideoFrame()
{
	swapVideoFrontBuffer();
	return video_front;
}

uint8_t* Kinect::getVideoFrameYUV()
{
	swapVideoFrontBuffer();

	if(alt_video_source == NULL)
		Bitmap2Yuv420p(yuv_front, (uint8_t*)video_front, 640, 480);
	else
		Bitmap2Yuv420p(yuv_front, alt_video_source, 640, 480);

	return yuv_front;
}

Kinect::depth_buffer* Kinect::getDepthFrame()
{
	swapDepthFrontBuffer();
	return depth_front;
}

void Kinect::process_events()
{
	assert(freenect_process_events(f_ctx) >= 0);
}

void Kinect::setVideoSource(uint8_t* frame)
{
	alt_video_source = frame;
}
