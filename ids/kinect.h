#ifndef KINECT_H
#define KINECT_H

#include <stdexcept>
#include <pthread.h>
#include <cstdlib>

#include "libfreenect.h"

class Kinect
{
	protected: //Internal types
		typedef uint8_t depth_buffer[480][640][2];
		typedef uint8_t video_buffer[480][640][3];

	protected: //Static Singleton Class
		static class Kinect* Singleton;
	protected: //Singleton Constructor
		Kinect();
	public: //Public Singleton Entry point
		static Kinect* getSingleton();

	protected: //Instance Members

		/*Freenect settings*/
		freenect_context *f_ctx;
		freenect_device *f_dev;

		/*Buffers for depth sensor and video*/
		depth_buffer* depth_back;
		depth_buffer* depth_mid;
		depth_buffer* depth_front;
		video_buffer* video_back;
		video_buffer* video_mid;
		video_buffer* video_front;

		/*Buffer Mutexes*/
		pthread_mutex_t depth_lock;
		pthread_mutex_t video_lock;

	protected: //Internal Members

		void initFreenect();

		/*Swap image buffers*/
		void swapVideoBackBuffer();
		void swapDepthBackBuffer();
		void swapVideoFrontBuffer();
		void swapDepthFrontBuffer();

		/*Callbacks for interfacing with Kinect*/
		static void video_cb(freenect_device *dev, void *rgb, uint32_t timestamp);
		static void depth_cb(freenect_device *dev, void *depth, uint32_t timestamp);
	public:

		/*Grab front buffers*/
		video_buffer* getVideoFrame();
		depth_buffer* getDepthFrame();

		/*Deconstructor*/
		~Kinect();
};

#endif
