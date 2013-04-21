#include "mapframe.h"

#define SECTOR_INCHES 1

inline float quick_square(float x)
{
	return x*x;
}

ComMapFrame::ComMapFrame() : ComFrame::ComFrame("MapFrame")
{
}

int ComMapFrame::action(IDS* main)
{
	int x,y,xo,yo;
	Kinect::depth_buffer* dframe = main->getDepth();
	Kinect* kinect = main->getKinect();
	Minotaur minotaur = main->getMinotaur();

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
	float sin_ori = sin(minotaur.orient);
	float cos_ori = cos(minotaur.orient);

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
						fd = 3480*254/(1091.5-(float)d);

						rx = kinect->x3d(x,y,xo,yo,fd);
						ry = kinect->y3d(x,y,xo,yo,fd);
						rz = kinect->z3d(x,y,xo,yo,fd);

						p3d[yo][xo].x = rx * cos_ori - ry * sin_ori + minotaur.x;
						p3d[yo][xo].y = rx * sin_ori + ry * cos_ori + minotaur.y;
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
				xSS /= valid;

				slopeyx = (xybar - avg3d.x * avg3d.y) / (xSS - quick_square(avg3d.x));
				yint = avg3d.y - slopeyx * avg3d.x;

				if((sqrt(zvariance) < sqrt(xvariance + yvariance) * 0.8) || (zvariance < 150*150*valid))
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
					continue;
					
					residual_bar = 0;
					residual_xbar = 0;
					residual_ybar = 0;
					for(yo = 0; yo < 8; yo++)
						for(xo = 0; xo < 8; xo++)
							if(valid_points[yo][xo])
							{
								residual_bar += quick_square((p3d[yo][xo].y - slopeyx * p3d[yo][xo].x - yint));
								residual_xbar += quick_square(p3d[yo][xo].y - avg3d.y);
								residual_ybar += quick_square(p3d[yo][xo].x - avg3d.x);
							}


					
					if(residual_bar <= valid * 225 && sqrt(residual_xbar + residual_ybar)  <= valid * 175)
					{
						r = 0;
						g = 255-std::min<int>(std::max<int>(128+atan(slopeyx)*64,0),255);//std::min<int>(std::max<int>(yint*20+128,0),255);
						b = std::min<int>(std::max<int>(128+atan(slopeyx)*64,0),255);
					}else{
						//Antiplanar obstacle
						r = 0x00;
						g = 0x00;
						b = 0x00;
					}
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

