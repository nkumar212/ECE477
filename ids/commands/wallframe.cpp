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
	for(d = 1; d <= KINECT_CALIB_DOFF; d++)
		decode_kinect_dist[d] = (KINECT_CALIB_LOGM*log(KINECT_CALIB_DOFF-d)+KINECT_CALIB_LOGB) * 100;
}

int ComWallFrame::action(IDS* main)
{
	int x,y,xo,yo, Y;
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
	float resid_yx, resid_zx, resid_zy;
	uint8_t r,g,b;
	uint16_t d, d0, d1;
	float fd;
	float floor_height = 0;
	int floor_count = 0;
	float rx, ry, rz;
	float sin_ori = sin(minostate.orient);
	float cos_ori = cos(minostate.orient);
	float origin_dist;
	float avg_dist;
	float orient_yx;

	uint32_t count, max_count = 0;

	Wall avg_walls[480/8/WALL_AVG_SIZE][640/8/WALL_AVG_SIZE][WALL_AVG_SIZE][WALL_AVG_SIZE];
	bool valid_walls[480/8/WALL_AVG_SIZE][640/8/WALL_AVG_SIZE][WALL_AVG_SIZE][WALL_AVG_SIZE];

	int nslope = 480;
	int nodist = 256;
	int nodist_half = nodist / 2 + 1;
	double fft_data[nslope][nodist];
	fftw_complex* fft_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*nslope*nodist_half);

	float avg_slope, avg_yint;

	int fail_yx_res = 0;
	int fail_zx_res = 0;
	int fail_zy_res = 0;

	int fail_floor_check1 = 0;
	int fail_floor_check2 = 0;
	int fail_floor_check3 = 0;
	int fail_floor_check4 = 0;

	bool wall_check1, wall_check2, wall_check3;
	bool floor_check1, floor_check2, floor_check3, floor_check4;

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

	for(x = 0; x < nodist; x++)
		for(y = 0; y < nslope; y++)
			fft_data[y][x] = fft_data[y][x] = 0;

	for(y = 0; y < 480/8; y++)
	{
		for(x = 0; x < 640/8; x++)
		{
			avg3d = {0,0,0};
			avg_dist = 0;
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

					if(d != 0x07FF && d <= KINECT_CALIB_DOFF)
					{
						fd = decode_kinect_dist[d];

						avg_dist += fd;
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
					
				resid_yx = 0;
				resid_zx = 0;
				resid_zy = 0;
				for(yo = 0; yo < 8; yo++)
					for(xo = 0; xo < 8; xo++)
						if(valid_points[yo][xo])
						{
							resid_yx += quick_square((p3d[yo][xo].y - slopeyx * p3d[yo][xo].x - yint));
							resid_zx += quick_square((p3d[yo][xo].z - slopezx * p3d[yo][xo].x - zxint));
							resid_zy += quick_square((p3d[yo][xo].z - slopezy * p3d[yo][xo].y - zyint));
						}

				floor_check1 = fabs(atan(slopezx)) < 0.262;
				floor_check2 = fabs(atan(slopezy)) < 0.262;
				floor_check3 = resid_zx * 50000 < valid * quick_square(avg_dist/100);
				floor_check4 = resid_zy * 50000 < valid * quick_square(avg_dist/100);

				if(floor_check1 && floor_check2 && floor_check3 && floor_check4)
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
					//r = std::min<int>(std::max<int>(resid_yx*20,0),255);

					wall_check1 = resid_yx * 1000 < valid * quick_square(avg_dist/100);

					if(wall_check1 && !floor_check3 && !floor_check4)
					{
						//Using minimum distance to robot point location for hashing, less likely to be out of range.
						origin_dist = (slopeyx * minostate.x - minostate.y + yint) / sqrt(quick_square(slopeyx)+1);
						orient_yx = fmod((atan(slopeyx) + PI / 2),PI);

						fft_data[(int)(orient_yx / PI * nslope / 2)][(int)(origin_dist/100) + nodist/4]++;
						fft_data[(int)(orient_yx / PI * nslope / 2 + nslope / 2)][(int)(origin_dist/100) + nodist/4]++;

						avg_walls[y/WALL_AVG_SIZE][x/WALL_AVG_SIZE][y % WALL_AVG_SIZE][x % WALL_AVG_SIZE] = Wall(slopeyx, yint);
						valid_walls[y/WALL_AVG_SIZE][x/WALL_AVG_SIZE][y % WALL_AVG_SIZE][x % WALL_AVG_SIZE] = true;
						r = 0;
						g = 255-std::min<int>(std::max<int>(orient_yx / PI * 256,0),255);//std::min<int>(std::max<int>(yint*20+128,0),255);
						b = std::min<int>(std::max<int>(orient_yx / PI * 256,0),255);

					}else{
						r = g = b = 0x80;
						if(!wall_check1)
							fail_yx_res++;
						
						if(!floor_check1) fail_floor_check1++;
						if(!floor_check2) fail_floor_check2++;
						if(!floor_check3) fail_floor_check3++;
						if(!floor_check4) fail_floor_check4++;
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

	//std::cerr << fail_yx_res << " " << fail_floor_check1 << " " << fail_floor_check2 << " " << fail_floor_check3 << " " << fail_floor_check4 << std::endl;

	fftw_plan fft = fftw_plan_dft_r2c_2d(nslope, nodist, &(fft_data[0][0]), fft_out, FFTW_ESTIMATE);
	fftw_execute(fft);
	fftw_destroy_plan(fft);

	double mag;
	double stddev_x, stddev_y;
	double var_x, var_y;
	double mean_x, mean_y;
	double filter_x, filter_y;
	double coeff_x, coeff_y;

	stddev_x = 2;
	stddev_y = 2;
	mean_x = 0;
	mean_y = nslope / 2;
	var_x = quick_square(x);
	var_y = quick_square(y);
	coeff_x = 1 / (stddev_x * sqrt(2*PI)) / 0.4;
	coeff_y = 1 / (stddev_y * sqrt(2*PI)) / 0.4;


	for(y = 0; y < nslope; y++)
	{
		Y = (nslope / 2 + y) % nslope;
//		filter_y = coeff_y * exp(-1 * quick_square(mean_y - y) / (2*var_y)); 
		for(x = 0; x < nodist_half; x++)
		{
			/*filter_x = fabs(coeff_x * exp(-1 * quick_square(mean_x - x) / (2*var_x))); 
			fft_out[Y*nodist_half+x][0] *= filter_x * filter_y;
			fft_out[Y*nodist_half+x][1] *= filter_x * filter_y;
			continue;*/

			if(abs(y - nslope / 2) >= 8 || x >= 8)
			{
				fft_out[Y*nodist_half+x][0] = 0;
				fft_out[Y*nodist_half+x][1] = 0;
			}else{
				mag = sqrt(quick_square(fft_out[Y*nodist_half+x][0]) + quick_square(fft_out[Y*nodist_half+x][1]));

	/*			frame[y][x][0] = mag / fft_out[0][0]*256;
				frame[y][x][1] = mag / fft_out[0][0]*256;
				frame[y][x][2] = mag / fft_out[0][0]*256;*/
			}
		}
	}

	fft = fftw_plan_dft_c2r_2d(nslope, nodist, fft_out, &(fft_data[0][0]), FFTW_ESTIMATE);
	fftw_execute(fft);
	fftw_destroy_plan(fft);

	double max_mag = 0, maxgrad;
	int maxgradid;

	std::set< Wall > walls;
	std::set< Wall >::iterator it_walls;

	for(y = 0; y < nslope; y++)
	{
		for(x = 0; x < nodist; x++)
		{
			mag = fft_data[y][x];
			if(mag > max_mag)
				max_mag = mag;
		}	
	}

	for(y = 0; y < nslope; y++)
	{
		for(x = 0; x < nodist; x++)
		{
			maxgrad = 0;
			maxgradid = 0;
			for(yo = -1; yo <= 1; yo++)
				for(xo = -1; xo <= 1; xo++)
					if(fft_data[y + yo][x + xo] > maxgrad)
					{
						maxgrad = fft_data[y + yo][x + xo];
						maxgradid = yo * 3 + xo;
					}

			mag = std::max<double>(fft_data[y][x],0);

			if(maxgradid != 0)
			{
				frame[y][x][0] = mag / max_mag * 255;
				frame[y][x][1] = mag / max_mag * 255;
				frame[y][x][2] = mag / max_mag * 255;
			}else if(abs(y - nslope/2) <= nslope/4){
				frame[y][x][0] = mag / max_mag * 255;
				frame[y][x][1] = 0;
				frame[y][x][2] = 0;
				
				if(mag > 125893) //10 ** 5.1
					walls.insert(Wall(fmod((float)y / nslope * 2 * PI,PI) - PI / 2,(float)x - nodist / 4.0));
			}
		}
	}

	for(it_walls = walls.begin(); it_walls != walls.end(); it_walls++)
	{
		std::cerr << " " << it_walls->orient / PI;
		std::cerr << " " << it_walls->yint;
		std::cerr << " " << log10(max_mag);
		std::cerr << std::endl;
	}

	std::cerr << std::endl;


	fftw_free(fft_out);

/*	double prev_count = fft_data[255] > 3000 ? fft_data[255] : -1;
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

	std::cerr << std::endl;*/

	return 0;
}

