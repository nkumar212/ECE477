#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define SUPER_SIZE 8
#define SUPER_SIZE_POWER 3

typedef struct
{
	char x_slope;
	char y_slope;
	char var;
} superpixel;

typedef short pixelblock[SUPER_SIZE][SUPER_SIZE*2];

static inline superpixel do_superpx(pixelblock block)
{
	short x_sum[SUPER_SIZE];
	short y_sum[SUPER_SIZE];

	short x_slope_sum = 0;
	short y_slope_sum = 0;
	int variance = 0;

	char row, col, i;

	superpixel ret;

	memset(x_sum,0,sizeof x_sum);
	memset(y_sum,0,sizeof y_sum);

	for(row = 0; row < SUPER_SIZE; row++)
	{
		for(col = 0; col < SUPER_SIZE; col++)
		{
			x_sum[row] += block[row][col*2] & 0x00FF;
			y_sum[col] += block[row][col*2] & 0x00FF;
		}
	}

	for(i = 1; i < SUPER_SIZE; i++)
	{
		x_slope_sum += x_sum[i-1] - x_sum[i];
		y_slope_sum += y_sum[i-1] - y_sum[i];
	}

	x_slope_sum >>= SUPER_SIZE_POWER;
	y_slope_sum >>= SUPER_SIZE_POWER;

	for(i = 1; i < SUPER_SIZE; i++)
	{
		variance += pow((x_sum[i-1] - x_sum[i] - x_slope_sum) >> SUPER_SIZE_POWER,2);
		variance += pow((y_sum[i-1] - y_sum[i] - y_slope_sum) >> SUPER_SIZE_POWER,2);
	}

	ret.x_slope = x_slope_sum >> SUPER_SIZE_POWER;
	ret.y_slope = y_slope_sum >> SUPER_SIZE_POWER;
	ret.variance = min(variance,255);

	return ret;
}

void depth2super_rgb(uint8_t* depth, uint8_t* rgb)
{
	superpixel sp_array[480 / SUPER_SIZE][640 / SUPER_SIZE];
	pixelblock tmp;

	register short row, col, spxrow;
	for(row = 0; row < 480; row += SUPER_SIZE)
	{
		for(col = 0; col < 640 * 2; col += SUPER_SIZE * 2)
		{
			for(spxrow = row; spxrow < row + SUPER_SIZE; spxrow++)
				memcpy(
					&tmp+row*SUPER_SIZE*2,
					depth + 640 * 2 * row + col,
				       	SUPER_SIZE*2
				);

			sp_array[row / SUPER_SIZE][col / SUPER_SIZE / 2];
		}
	}
}
