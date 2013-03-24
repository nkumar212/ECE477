/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2010 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libfreenect.h"
#include <jpeglib.h>
#include <unistd.h>

#include <pthread.h>
#include <math.h>
#include <time.h>

pthread_t freenect_thread;
volatile int die = 0;

int g_argc;
char **g_argv;

int window;


// back: owned by libfreenect (implicit for depth)
// mid: owned by callbacks, "latest frame ready"
// front: owned by GL, "currently being drawn"
uint8_t *depth_mid, *depth_front;
uint8_t *rgb_back, *rgb_mid, *rgb_front, *yuv_out;


freenect_context *f_ctx;
freenect_device *f_dev;
int freenect_angle = 0;
int freenect_led;

freenect_video_format requested_format = FREENECT_VIDEO_RGB;
freenect_video_format current_format = FREENECT_VIDEO_RGB;

int got_rgb = 0;
int got_depth = 0;

void Bitmap2Yuv420p( uint8_t *destination, uint8_t *rgb,
                     const int width, const int height ) {
	const size_t image_size = width * height;
	uint8_t *dst_y = destination;
	uint8_t *dst_u = destination + image_size/4;
	uint8_t *dst_v = destination + image_size/4 + image_size/16;
	int i,x,y,j=0;

	// Y plane
	for( i = 0; i < image_size; ++i ) {
		if((i % 2) && (i / 640 % 2))
		{
			*dst_y++ = ( ( 66*rgb[3*i] + 129*rgb[3*i+1] + 25*rgb[3*i+2] ) >> 8 ) + 16;
		}
	}

	// U plane
	for( y=0; y<height; y+=4 ) {
		for( x=0; x<width; x+=4 ) {
			i = y*width + x;
			++j;
			*dst_u++ = ( ( -38*rgb[3*i] + -74*rgb[3*i+1] + 112*rgb[3*i+2] ) >> 8 ) + 128;
		}
	}

	// V plane
	for( y=0; y<height; y+=4 ) {
		for( x=0; x<width; x+=4 ) {
			i = y*width + x;
			*dst_v++ = ( ( 112*rgb[3*i] + -94*rgb[3*i+1] + -18*rgb[3*i+2] ) >> 8 ) + 128;
		}
	}
}

int write_jpeg_file(unsigned char* raw_image, char *filename)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	/* this is a pointer to one row of image data */
	JSAMPROW row_pointer[1];
	FILE *outfile = fopen( filename, "wb" );

	if ( !outfile )
	{
		fprintf(stderr,"Error opening output jpeg file %s\n!", filename );
		return -1;
	}
	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);

	/* Setting the parameters of the output file here */
	cinfo.image_width = 640;
	cinfo.image_height = 480;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;
	/* default compression parameters, we shouldn't be worried about these */

	jpeg_set_defaults( &cinfo );
	cinfo.num_components = 3;
	//cinfo.data_precision = 4;
	cinfo.dct_method = JDCT_FLOAT;
	jpeg_set_quality(&cinfo, 15, TRUE);
	/* Now do the compression .. */
	jpeg_start_compress( &cinfo, TRUE );
	/* like reading a file, this time write one row at a time */
	while( cinfo.next_scanline < cinfo.image_height )
	{
		row_pointer[0] = &raw_image[ cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
		jpeg_write_scanlines( &cinfo, row_pointer, 1 );
	}
	/* similar to read file, clean up after we're done compressing */
	jpeg_finish_compress( &cinfo );
	jpeg_destroy_compress( &cinfo );
	fclose( outfile );
	/* success code is 1! */
	return 1;
}

uint16_t t_gamma[2048];

void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp)
{
	int i;
	uint16_t *depth = (uint16_t*)v_depth;
	fwrite(depth,640*2,480,stdout);
	got_depth++;
	return;

	for (i=0; i<640*480; i++) {
		int pval = t_gamma[depth[i]];
		int lb = pval & 0xff;

		depth_mid[3*i] = lb;
		depth_mid[3*i+1] = lb;
		depth_mid[3*i+2] = lb;
		
		continue;

		switch (pval>>8) {
			case 0:
				depth_mid[3*i+0] = 255;
				depth_mid[3*i+1] = 255-lb;
				depth_mid[3*i+2] = 255-lb;
				break;
			case 1:
				depth_mid[3*i+0] = 255;
				depth_mid[3*i+1] = lb;
				depth_mid[3*i+2] = 0;
				break;
			case 2:
				depth_mid[3*i+0] = 255-lb;
				depth_mid[3*i+1] = 255;
				depth_mid[3*i+2] = 0;
				break;
			case 3:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 255;
				depth_mid[3*i+2] = lb;
				break;
			case 4:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 255-lb;
				depth_mid[3*i+2] = 255;
				break;
			case 5:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+2] = 255-lb;
				break;
			default:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+2] = 0;
				break;
		}
	}
	got_depth++;
}

void rgb_cb(freenect_device *dev, void *rgb, uint32_t timestamp)
{
	// swap buffers
	assert (rgb_back == rgb);
	rgb_back = rgb_mid;
	freenect_set_video_buffer(dev, rgb_back);
	rgb_mid = (uint8_t*)rgb;
	//write_jpeg_file(rgb_mid, "test.jpg");
	fprintf(stderr,"0x%X\n", rgb);

	got_rgb++;
}

int64_t timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
	return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
		((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}

void *transcode(void* arg)
{
	struct timespec start, end;
	int iwait = 0;
	clock_gettime(CLOCK_MONOTONIC, &start);
	clock_gettime(CLOCK_MONOTONIC, &end);
	uint8_t* rgb_tmp;

	while (!die)
	{
		iwait = 0;
		while(timespecDiff(&end, &start) < 1000000000 / 23.98)
		{
			iwait++;
			usleep(500);
			clock_gettime(CLOCK_MONOTONIC, &end);
		}
		start = end;

		rgb_tmp = rgb_mid;
		rgb_mid = rgb_front;
		rgb_front = rgb_tmp;

		fprintf(stderr,"Frame %d 0x%X\n",iwait, rgb_front);

		Bitmap2Yuv420p(yuv_out, rgb_front, 640, 480);
		fwrite(yuv_out,320*6/4,240,stdout);
	}

	return NULL;
}

//void *freenect_threadfunc(void *arg)
void *freenect_threadfunc()
{
	int accelCount = 0;

	freenect_set_tilt_degs(f_dev,freenect_angle);
	freenect_set_led(f_dev,LED_GREEN);
	freenect_set_depth_callback(f_dev, depth_cb);
	freenect_set_video_callback(f_dev, rgb_cb);
	freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, current_format));
	freenect_set_depth_mode(f_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_11BIT));
	freenect_set_video_buffer(f_dev, rgb_back);

	freenect_start_depth(f_dev);
//	freenect_start_video(f_dev);

	while (!die && freenect_process_events(f_ctx) >= 0) {
		if (requested_format != current_format) {
			freenect_stop_video(f_dev);
			freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, requested_format));
			freenect_start_video(f_dev);
			current_format = requested_format;
		}
		usleep(500);
	}

	fprintf(stderr,"\nshutting down streams...\n");

//	freenect_stop_depth(f_dev);
	freenect_stop_video(f_dev);

	freenect_close_device(f_dev);
	freenect_shutdown(f_ctx);

	fprintf(stderr,"-- done!\n");
	return NULL;
}

int main(int argc, char **argv)
{
	int res;

	depth_mid = (uint8_t*)malloc(640*480*3);
	depth_front = (uint8_t*)malloc(640*480*3);
	rgb_back = (uint8_t*)malloc(640*480*3);
	rgb_mid = (uint8_t*)malloc(640*480*3);
	rgb_front = (uint8_t*)malloc(640*480*3);
	yuv_out = (uint8_t*)malloc(320*240*3);

	int i;
	for (i=0; i<2048; i++) {
		float v = i/2048.0;
		v = powf(v, 3)* 6;
		t_gamma[i] = v*6*256;
	}

	g_argc = argc;
	g_argv = argv;

	if (freenect_init(&f_ctx, NULL) < 0) {
		fprintf(stderr,"freenect_init() failed\n");
		return 1;
	}

	freenect_set_log_level(f_ctx, FREENECT_LOG_DEBUG);
	freenect_select_subdevices(f_ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));

	int nr_devices = freenect_num_devices (f_ctx);
	fprintf (stderr,"Number of devices found: %d\n", nr_devices);

	int user_device_number = 0;
	if (argc > 1)
		user_device_number = atoi(argv[1]);

	if (nr_devices < 1) {
		freenect_shutdown(f_ctx);
		return 1;
	}

	if (freenect_open_device(f_ctx, &f_dev, user_device_number) < 0) {
		fprintf(stderr,"Could not open device\n");
		freenect_shutdown(f_ctx);
		return 1;
	}

//	res = pthread_create(&freenect_thread, NULL, transcode, NULL);

/*	getc(stdin);

	if (res) {
		printf("pthread_create failed\n");
		freenect_shutdown(f_ctx);
		return 1;
	}*/

	freenect_threadfunc();
	die = 1;

	return 0;
}
