#include "wallframe.h"

uint8_t color_alphabet[26][3] = 
{
	{240,163,255},
	{0,117,220},
	{153,63,0},
	{76,0,92},
	{25,25,25},
	{0,92,49},
	{43,206,72},
	{255,204,153},
	{128,128,128},
	{148,255,181},
	{143,124,0},
	{157,204,0},
	{194,0,136},
	{0,51,128},
	{255,164,5},
	{255,168,187},
	{66,102,0},
	{255,0,16},
	{94,241,242},
	{0,153,143},
	{224,255,102},
	{116,10,255},
	{153,0,0},
	{255,255,128},
	{255,255,0},
	{255,80,5}
};

inline float quick_square(float x)
{
	return x*x;
}

ComWallFrame::ComWallFrame() : ComFrame::ComFrame("WallFrame")
{
	int d;
	for(d = 1; d < 1029; d++)
		decode_kinect_dist[d] = (-45.7768687166*log(1028-d)+295.5003224073) * 100;
}

int ComWallFrame::action(IDS* main)
{
	int x,y,xo,yo;
	Kinect::depth_buffer* dframe = main->getDepth();
	Kinect* kinect = main->getKinect();
	Minotaur* minotaur = main->getMinotaur();
	Minotaur::MinotaurState minostate = minotaur->getState();

	Point p3d[8][8];
	Point avg3d;
	Point avgbar_flat;
	int valid;
	float zvariance, xvariance, yvariance, xSS, ySS, xybar, xzbar, yzbar;
	float slopeyx, slopezx, slopezy;
	float yint, zxint, zyint;
	float residual_bar, residual_zxbar, residual_zybar;
	uint8_t r,g,b;
	uint16_t d, d0, d1;
	float fd;
	float floor_height = 0;
	int floor_count = 0;
	float rx, ry, rz;
	float sin_ori = sin(minostate.orient);
	float cos_ori = cos(minostate.orient);
	float origin_dist;

	uint32_t count, max_count = 0;

	Wall avg_walls[480/8/WALL_AVG_SIZE][640/8/WALL_AVG_SIZE][WALL_AVG_SIZE][WALL_AVG_SIZE];
	bool valid_walls[480/8/WALL_AVG_SIZE][640/8/WALL_AVG_SIZE][WALL_AVG_SIZE][WALL_AVG_SIZE];

	int ny = 256;
	int nx = 256;
	double fft_data[256];
	fftw_complex* fft_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*nx);


	std::map<Wall,int> wallmap;
	std::map<Wall,int>::iterator it_walls;

	float avg_slope, avg_yint;

	int fail_yx_res = 0;
	int fail_zx_res = 0;
	int fail_zy_res = 0;

	if(main->getDepthCount() <= 0)
	{
		std::cerr << "MapFrame awaiting depth data" << std::endl;
		return 1;
	}

	for(y = 0; y < 480/8/WALL_AVG_SIZE; y++)
		for(x = 0; x < 640/8/WALL_AVG_SIZE; x++)
			for(yo = 0; yo < WALL_AVG_SIZE; yo++)
				for(xo = 0; xo < WALL_AVG_SIZE; xo++)
					valid_walls[y][x][yo][xo] = false;

	for(y = 0; y < 256; y++)
		fft_data[y] = fft_data[y] = 0;

	for(y = 0; y < 480/8; y++)
	{
		for(x = 0; x < 640/8; x++)
		{
			avg3d = {0,0,0};
			valid = 0;
			xybar = 0;

			for(yo = 0; yo < 8; yo++)
			{
				
				for(xo = 0; xo < 8; xo++)
				{
					d0 = (*dframe)[y*8+yo][x*8+xo][0];
					d1 = (*dframe)[y*8+yo][x*8+xo][1];
					d = d1;
					d = d << 8 | d0;

					if(d != 0x07FF)
					{
						fd = decode_kinect_dist[d];

						rx = kinect->x3d(x,y,xo,yo,fd);
						ry = kinect->y3d(x,y,xo,yo,fd);
						rz = kinect->z3d(x,y,xo,yo,fd);

						p3d[yo][xo].x = rx * cos_ori - ry * sin_ori + minostate.x;
						p3d[yo][xo].y = rx * sin_ori + ry * cos_ori + minostate.y;
						p3d[yo][xo].z = rz;

						avg3d.x += p3d[yo][xo].x;
						avg3d.y += p3d[yo][xo].y;
						avg3d.z += p3d[yo][xo].z;

						valid_points[yo][xo] = true;
						++valid;
					}else
						valid_points[yo][xo] = false;
						//p3d[yo][xo].valid = false;
				}
			}

			avg3d.x /= valid;
			avg3d.y /= valid;
			avg3d.z /= valid;

			if(valid <= (8*8)*3/4)
			{
				//Not enough data to represent the points
				r = 0x00;
				g = 0x00;
				b = 0x00;
			}else{

				//Calculate statistics for slope calculation
				zvariance = 0;
				xvariance = 0;
				yvariance = 0;
				xSS = 0, ySS = 0;
				xybar = 0, xzbar = 0, yzbar = 0;
				for(yo = 0; yo < 8; yo++)
					for(xo = 0; xo < 8; xo++)
					{
						if(valid_points[yo][xo])
						{
							xvariance += quick_square(p3d[yo][xo].x-avg3d.x);
							yvariance += quick_square(p3d[yo][xo].y-avg3d.y);
							zvariance += quick_square(p3d[yo][xo].z-avg3d.z);

							xSS += quick_square(p3d[yo][xo].x);
							ySS += quick_square(p3d[yo][xo].y);
							xybar += p3d[yo][xo].x * p3d[yo][xo].y;
							xzbar += p3d[yo][xo].x * p3d[yo][xo].z;
							yzbar += p3d[yo][xo].y * p3d[yo][xo].z;
						}
					}

				xybar /= valid;
				xzbar /= valid;
				yzbar /= valid;
				xSS /= valid;
				ySS /= valid;

				slopeyx = (xybar - avg3d.x * avg3d.y) / (xSS - quick_square(avg3d.x));
				slopezx = (xzbar - avg3d.x * avg3d.z) / (xSS - quick_square(avg3d.x));
				slopezy = (yzbar - avg3d.y * avg3d.z) / (ySS - quick_square(avg3d.y));
				yint = avg3d.y - slopeyx * avg3d.x;
				zxint = avg3d.z - slopezx * avg3d.x;
				zyint = avg3d.z - slopezy * avg3d.y;

				if(zvariance < valid*300)
				{
					//Floor or ceiling at a constant height from Kinect
					if(avg3d.z < -800 && avg3d.z > -1600)
					{
						r = 0xFF;
						g = 0xFF;
						b = 0xFF;
						floor_height += avg3d.z;
						floor_count++;
					}else{
						r = 0xFF;
						g = 0x00;
						b = 128 + avg3d.z / 12 / 100 * 256;
					}
				}else{
					//Wall or non-plane
					
					residual_bar = 0;
					residual_zxbar = 0;
					residual_zybar = 0;
					for(yo = 0; yo < 8; yo++)
						for(xo = 0; xo < 8; xo++)
							if(valid_points[yo][xo])
							{
								residual_bar += quick_square((p3d[yo][xo].y - slopeyx * p3d[yo][xo].x - yint));
								residual_zxbar += quick_square((p3d[yo][xo].z - slopezx * p3d[yo][xo].x - zxint));
								residual_zybar += quick_square((p3d[yo][xo].z - slopezy * p3d[yo][xo].y - zyint));
							}
					//r = std::min<int>(std::max<int>(residual_bar*20,0),255);

					if((residual_bar <= valid*220) && (((residual_zxbar > valid*100) && (residual_zybar > valid*100)) || isinff(slopezy) || isinff(slopezx)))
					{
						//Using minimum distance to robot point location for hashing, less likely to be out of range.
						origin_dist = (slopeyx * minostate.x - minostate.y + yint) / sqrt(quick_square(slopeyx)+1);

						//Magic number hashes radians into 0-255 addresses
						fft_data[(int)(atan(slopeyx)*81.487330864+128)]++;

						avg_walls[y/WALL_AVG_SIZE][x/WALL_AVG_SIZE][y % WALL_AVG_SIZE][x % WALL_AVG_SIZE] = Wall(slopeyx, yint);
						valid_walls[y/WALL_AVG_SIZE][x/WALL_AVG_SIZE][y % WALL_AVG_SIZE][x % WALL_AVG_SIZE] = true;

						r = 0;
						g = 255-std::min<int>(std::max<int>(128+atan(slopeyx)*64,0),255);//std::min<int>(std::max<int>(yint*20+128,0),255);
						b = std::min<int>(std::max<int>(128+atan(slopeyx)*64,0),255);

						wallmap[Wall(atan(avg_slope),avg_yint)] += count;
					}else{
						r = g = b = 0;
						if(residual_bar <= valid * 220)
							fail_yx_res++;
						if(residual_zxbar > valid*100 && !isinff(slopezx))
							fail_zx_res++;
						if(residual_zybar > valid*100 && !isinff(slopezy))
							fail_zy_res++;
					}
				}
			}

			for(yo = 0; yo < 8; yo++)
				for(xo = 0; xo < 8; xo++)
				{
					frame[y*8+yo][x*8+xo][0] = r;
					frame[y*8+yo][x*8+xo][1] = g;
					frame[y*8+yo][x*8+xo][2] = b;
				}
		}
	}

	fftw_plan fft = fftw_plan_dft_r2c_1d(nx, &(fft_data[0]), fft_out, FFTW_ESTIMATE);
	fftw_execute(fft);
	fftw_destroy_plan(fft);

/*	double mag;
	for(x = 0; x < 128; x++)
	{
		mag = sqrt(quick_square(fft_out[x][0]) + quick_square(fft_out[x][1]));
		for(y = 0; y < 256; y++)
		{
			frame[y][x][0] = log(mag)/log(10)*10;
			frame[y][x][1] = log(mag)/log(10)*10;
			frame[y][x][2] = log(mag)/log(10)*10;
		}
	}*/

	for(x = 0; x < 129; x++)
	{
		if(x > 7)
			fft_out[x][0] = fft_out[x][1] = 0;
	}

	fft = fftw_plan_dft_c2r_1d(256, fft_out, &(fft_data[0]), FFTW_ESTIMATE);
	fftw_execute(fft);
	fftw_destroy_plan(fft);

/*	for(x = 0; x < 256; x++)
	{
		for(y = 0; y < 256; y++)
		{
			frame[y][x][0] = log(fft_data[x])/log(10)*10;
			frame[y][x][1] = log(fft_data[x])/log(10)*10;
			frame[y][x][2] = log(fft_data[x])/log(10)*10;
		}
	}*/


	fftw_free(fft_out);

	double prev_count = fft_data[255] > 3000 ? fft_data[255] : -1;
	double prev_count_2 = fft_data[254] > 3000 ? fft_data[254] : -1;

	for(y = 0; y < 256; y++)
	{
		if(fft_data[y] > 3000)
		{
			if(prev_count != -1 && prev_count > fft_data[y] && prev_count_2 < prev_count && prev_count_2 != -1)
				std::cerr << (y-128)*(1/81.487330864) << "\t" << fft_data[y] << std::endl;
			prev_count_2 = prev_count;
			prev_count = fft_data[y];
		}else{
			prev_count = -1;
		}
	}

	std::cerr << std::endl;

	return 0;

	for(y = 0; y < 480/8/WALL_AVG_SIZE; y++)
		for(x = 0; x < 640/8/WALL_AVG_SIZE; x++)
		{
			avg_slope = 0;
			avg_yint = 0;
			count = 0;
			for(yo = 0; yo < WALL_AVG_SIZE; yo++)
				for(xo = 0; xo < WALL_AVG_SIZE; xo++)
				{
					if(valid_walls[y][x][yo][xo])
					{
						avg_slope += avg_walls[y][x][yo][xo].orient;
						avg_yint += avg_walls[y][x][yo][xo].yint;
						++count;
					}
				}

			if(count >= WALL_AVG_SIZE * 0.75)
			{
				avg_slope /= count;
				avg_yint /= count;

				r = 0;
				g = 255-std::min<int>(std::max<int>(128+atan(avg_slope)*64,0),255);//std::min<int>(std::max<int>(yint*20+128,0),255);
				b = std::min<int>(std::max<int>(128+atan(avg_slope)*64,0),255);

				wallmap[Wall(atan(avg_slope),avg_yint)] += count;
			}else{
				r = g = b = 0;
			}

			for(yo = 0; yo < WALL_AVG_SIZE*8; yo++)
				for(xo = 0; xo < WALL_AVG_SIZE*8; xo++)
				{
					frame[y*8*WALL_AVG_SIZE+yo][x*8*WALL_AVG_SIZE+xo][0] = r;
					frame[y*8*WALL_AVG_SIZE+yo][x*8*WALL_AVG_SIZE+xo][1] = g;
					frame[y*8*WALL_AVG_SIZE+yo][x*8*WALL_AVG_SIZE+xo][2] = b;
				}
		}

	for(it_walls = wallmap.begin(); it_walls != wallmap.end(); it_walls++)
	{
		if(it_walls->second > 100)
			std::cerr << it_walls->first.orient << "\t" << it_walls->first.yint << "\t" << it_walls->second << std::endl;
	}

	std::cerr << std::endl;

	return 0;
}

