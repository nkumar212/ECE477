#ifndef KINECT_H
#define KINECT_H

#include <stdexcept>
#include <pthread.h>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <iostream>

#include "libfreenect.h"
#include "minotaur.h"

#define KINECT_DEPTH_HORIZ_PIXEL_THETA 0.0017159468
#define KINECT_DEPTH_VERT_PIXEL_THETA 0.001798352

//#define KINECT_DEPTH_HORIZ_PIXEL_THETA 0.0004159468
//#define KINECT_DEPTH_VERT_PIXEL_THETA 0.000498352

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

		struct Spherical
		{
/*			double sin_azi, cos_azi; //Functions of azimuth
			double sin_inc, cos_inc; //Functions of inclination*/
			float sin_azi, tan_inc;
		};


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

		Spherical sphericals[480/8][640/8][8][8];

	public:
		inline double x3d(int x, int y, int ix, int iy, float d)
		{
			Spherical sc = sphericals[y][x][iy][ix];
//			return d * fabs(sc.sin_inc) * (sc.sin_azi*m.cos_ori+sc.cos_azi*m.sin_ori);
			return d * sc.sin_azi;
		}

		inline double z3d(int x, int y, int ix, int iy, float d)
		{
			Spherical sc = sphericals[y][x][iy][ix];
			return d * sc.tan_inc;
		}

		inline double y3d(int x, int y, int ix, int iy, float d)
		{
			Spherical sc = sphericals[y][x][iy][ix];
			return d;
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
		video_buffer* nextVideoFrame();
		uint8_t* nextVideoFrameYUV();
		depth_buffer* getDepthFrame();
		void process_events();
		void setVideoSource(uint8_t* newvideobuffer);

		uint64_t getDepthCount();
		uint64_t getVideoCount();

		/*Deconstructor*/
		~Kinect();
};

#endif
