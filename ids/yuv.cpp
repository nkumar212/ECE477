#include <stdint.h>
#include <cstdio>

void Bitmap2Yuv420p( uint8_t *destination, uint8_t *rgb,
                     const int width, const int height ) {
	const size_t image_size = width * height;
	uint8_t *dst_y = destination;
	uint8_t *dst_u = destination + image_size/4;
	uint8_t *dst_v = destination + image_size/4 + image_size/16;
	register int i;

	for( i = 0; i < image_size; ++i ) {
		if((i % 2 == 0) && (i / 640 % 2 == 0))
		{
			*dst_y++ = ( ( 66*rgb[3*i] + 129*rgb[3*i+1] + 25*rgb[3*i+2] ) >> 8 ) + 16;
			if((i % 4 == 0) && ((i / 640) % 4 == 0))
			{
				*dst_u++ = ( ( -38*rgb[3*i] + -74*rgb[3*i+1] + 112*rgb[3*i+2] ) >> 8 ) + 128;
				*dst_v++ = ( ( 112*rgb[3*i] + -94*rgb[3*i+1] + -18*rgb[3*i+2] ) >> 8 ) + 128;
			}
		}
	}
}

