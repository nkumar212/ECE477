#ifndef KINECT_H
#define KINECT_H

class Kinect
{
	protected: //Internal types
		typedef void (*kinnect_cb)(freenect_device*, void*,uint32_t);
		typedef uint8_t depth_buffer[480][640][2];
		typedef uint8_t rgb_buffer[480][640][3];
	protected: //Static Singleton Class
		static class Kinect* Singleton;
	protected: //Singleton Constructor
		Kinect();
	public: //Public Singleton Entry point
		Kinect* getSingleton();

	protected: //Instance Members

		/*Freenect settings*/
		freenect_context *f_ctx;
		freenect_device *f_dev;

		/*Kinect Thread Control*/
		pthread_t freenect_thread;

		/*Callbacks for interfacing with Kinect*/
		kinnect_cb depth_cb;
		kinnect_cb rgb_cb;

		/*Buffers for depth sensor and video*/
		depth_buffer* depth_back;
		depth_buffer* depth_mid;
		depth_buffer* depth_front;
		rgb_buffer* video_back;
		rgb_buffer* video_mid;
		rgb_buffer* video_front;
};

#endif
