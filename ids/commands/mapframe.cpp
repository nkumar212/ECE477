#include "mapframe.h"

#define SECTOR_INCHES 3

inline float quick_square(float x)
{
	return x*x;
}

ComMapFrame::ComMapFrame() : ComFrame::ComFrame("MapFrame")
{
	int d;
	for(d = 1; d < 1029; d++)
		decode_kinect_dist[d] = (-45.7768687166*log(1028-d)+295.5003224073) * 100;
}

int ComMapFrame::action(IDS* main)
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

	int nslope = 480;
	int nodist = 256;
	int nodist_half = nodist / 2 + 1;

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

	Map* idsMap = main->getMap();
	Map::Sector* sector;

	if(main->getDepthCount() <= 0)
	{
		std::cerr << "MapFrame awaiting depth data" << std::endl;
		return 1;
	}

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

						p3d[yo][xo].x = rx * cos_ori + rx * sin_ori + minostate.x;
						p3d[yo][xo].y = ry * cos_ori - ry * sin_ori + minostate.y;
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
						idsMap->getPoint(avg3d.x/(SECTOR_INCHES * 100),avg3d.y/(SECTOR_INCHES * 100))->incOpen();
					}else{
						r = 0xFF;
						g = 0x00;
						b = 128 + avg3d.z / 12 / 100 * 256;
						idsMap->getPoint(avg3d.x/(SECTOR_INCHES * 100),avg3d.y/(SECTOR_INCHES * 100))->incClosed();
					}
				}else{
					idsMap->getPoint(avg3d.x/(SECTOR_INCHES * 100),avg3d.y/(SECTOR_INCHES * 100))->incClosed();
				}
			}
		}
	}

	for(y = 0; y < 480/8; y++)
	{
		for(x = 0; x < 640/8; x++)
		{
			sector = idsMap->getSector(x-640/16,y-480/16);

			for(yo = 0; yo < 8; yo++)
			{
				for(xo = 0; xo < 8; xo++)
				{
					if((x*8 - 640/2 +xo == (int)minostate.x) && (y*8 - 480 / 2 + yo == (int)minostate.y))
					{
						frame[y*8+yo][x*8+xo][0] = 0xFF;
						frame[y*8+yo][x*8+xo][1] = 0x00;
						frame[y*8+yo][x*8+xo][2] = 0x00;
					}else{
						frame[y*8+yo][x*8+xo][0] = sector->points[yo][xo].getProb();
						frame[y*8+yo][x*8+xo][1] = frame[y*8+yo][x*8+xo][0];
						frame[y*8+yo][x*8+xo][2] = frame[y*8+yo][x*8+xo][1];
					}
				}
			}
		}
	}
	return 0;
}

/*int ComMapFrame::action(IDS* main)
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
	float zvariance, xvariance, yvariance, xSS, xybar;
	float slopeyx, yint, residual_bar, residual_xbar, residual_ybar;
	uint8_t r,g,b;
	uint16_t d, d0, d1;
	float fd;
	float floor_height = 0;
	int floor_count = 0;

	float rx, ry, rz;
	float sin_ori = sin(minostate.orient);
	float cos_ori = cos(minostate.orient);

	Map* idsMap = main->getMap();
	Map::Sector* sector;

	if(main->getDepthCount() <= 0)
	{
		std::cerr << "MapFrame awaiting depth data" << std::endl;
		return 1;
	}

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
				xSS = 0;
				xybar = 0;
				for(yo = 0; yo < 8; yo++)
					for(xo = 0; xo < 8; xo++)
					{
						if(valid_points[yo][xo])
						{
							xvariance += quick_square(p3d[yo][xo].x-avg3d.x);
							yvariance += quick_square(p3d[yo][xo].y-avg3d.y);
							zvariance += quick_square(p3d[yo][xo].z-avg3d.z);

							xSS += quick_square(p3d[yo][xo].x);
							xybar += p3d[yo][xo].x * p3d[yo][xo].y;
						}
					}

				xybar /= valid;

				if(zvariance < valid*300)
				{
					//Floor or ceiling at a constant height from Kinect
					if(avg3d.z < -800 && avg3d.z > -1600)
					{
						idsMap->getPoint(avg3d.x/(SECTOR_INCHES * 100),avg3d.y/(SECTOR_INCHES * 100))->incOpen();
						r = 0xFF;
						g = 0xFF;
						b = 0xFF;
						floor_height += avg3d.z;
						floor_count++;
					}else{
						idsMap->getPoint(avg3d.x/(SECTOR_INCHES * 100),avg3d.y/(SECTOR_INCHES * 100))->incClosed();
						r = 0xFF;
						g = 0x00;
						b = 128 + avg3d.z / 12 / 100 * 256;
					}
				}else{
					//Wall or non-plane
					idsMap->getPoint(avg3d.x/(SECTOR_INCHES * 100),avg3d.y/(SECTOR_INCHES*100))->incClosed();
				}
			}
		}
	}

	for(y = 0; y < 480/8; y++)
	{
		for(x = 0; x < 640/8; x++)
		{
			sector = idsMap->getSector(x-640/16,y-480/16);

			for(yo = 0; yo < 8; yo++)
			{
				for(xo = 0; xo < 8; xo++)
				{
					if(y == 480/16 && x == 640/16 && xo == 4 && yo == 4)
					{
						frame[y*8+yo][x*8+xo][0] = 0xFF;
						frame[y*8+yo][x*8+xo][1] = 0x00;
						frame[y*8+yo][x*8+xo][2] = 0x00;
					}else{
						frame[y*8+yo][x*8+xo][0] = sector->points[yo][xo].getProb();
						frame[y*8+yo][x*8+xo][1] = frame[y*8+yo][x*8+xo][0];
						frame[y*8+yo][x*8+xo][2] = frame[y*8+yo][x*8+xo][1];
					}
				}
			}
		}
	}

	return 0;
}
*/
