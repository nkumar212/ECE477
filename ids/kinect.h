#ifndef KINECT_H
#define KINECT_H

#include <stdexcept>
#include <pthread.h>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cmath>

#include "libfreenect.h"

#define KINECT_DEPTH_HORIZ_PIXEL_THETA 0.0017159468
#define KINECT_DEPTH_VERT_PIXEL_THETA 0.001798352

void Bitmap2Yuv420p( uint8_t *destination, uint8_t *rgb,
                     const int width, const int height );

class Kinect
{
	public: //Internal types
		typedef uint8_t depth_buffer[480][640][2];
		typedef uint8_t video_buffer[480][640][3];
		typedef uint8_t yuv_buffer[240][320][3];

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

		/*Buffer for video source input*/
		uint8_t* alt_video_source;

		/*Count of video and depth frames*/
		static uint64_t depth_count;
		static uint64_t video_count;

		/*Buffer for YUV output*/		
		uint8_t* yuv_front;

		/*Buffer Mutexes*/
		pthread_mutex_t depth_lock;
		pthread_mutex_t video_lock;

		float x3dTrig[480/8][640/8][8][8];
		float y3dTrig[480/8][640/8][8][8];
		float z3dTrig[480/8][640/8][8][8];

	public:
		inline float x3d(int x, int y, int ix, int iy, float d)
		{
			return d*x3dTrig[y][x][iy][ix];
		}

		inline float y3d(int x, int y, int ix, int iy, float d)
		{
			return d*y3dTrig[y][x][iy][ix];
		}

		inline float z3d(int x, int y, int ix, int iy, float d)
		{
			return d*z3dTrig[y][x][iy][ix];
		}

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
		uint8_t* getVideoFrameYUV();
		depth_buffer* getDepthFrame();
		void process_events();
		void setVideoSource(uint8_t* newvideobuffer);

		uint64_t getDepthCount();
		uint64_t getVideoCount();

		/*Deconstructor*/
		~Kinect();
};

#endif
