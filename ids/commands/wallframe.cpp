#include "wallframe.h"

inline float quick_square(float x)
{
	return x*x;
}

ComWallFrame::ComWallFrame() : Command::Command("WallFrame")
{
	memset(frame,0,sizeof(Kinect::video_buffer));
}

int ComWallFrame::action(IDS* main)
{
	int x,y,xo,yo;
	Kinect::depth_buffer* dframe = main->getDepth();
	Kinect* kinect = main->getKinect();
	Minotaur minotaur = main->getMinotaur();

	Point p3d[8][8];
	Point avg3d;
	Point avgbar_flat;
	int valid;
	float zvariance, xSS, xybar;
	float slopeyx, yint, residual_bar, residual_xbar, residual_ybar;
	uint8_t r,g,b;
	uint16_t d, d0, d1;
	float fd;
	float floor_height = 0;
	int floor_count = 0;

	if(main->getDepthCount() <= 0)
	{
		std::cerr << "WallFrame awaiting depth data" << std::endl;
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
						fd = 3480*254/(1220.5-(float)d);
						p3d[yo][xo].x = kinect->x3d(x,y,xo,yo,fd,minotaur);
						p3d[yo][xo].y = kinect->y3d(x,y,xo,yo,fd);
						p3d[yo][xo].z = kinect->z3d(x,y,xo,yo,fd,minotaur);
						valid_points[yo][xo] = true;
						avg3d.x += p3d[yo][xo].x;
						avg3d.y += p3d[yo][xo].y;
						avg3d.z += p3d[yo][xo].z;
						++valid;
						xybar += p3d[yo][xo].x * p3d[yo][xo].y;
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
				r = 0x00;
				g = 0x00;
				b = 0xFF;
			}else{
				xybar /= valid;


				zvariance = 0;
				xSS = 0;
				for(yo = 0; yo < 8; yo++)
					for(xo = 0; xo < 8; xo++)
					{
						if(valid_points[yo][xo])
						{
							zvariance += sqrt(fabs(p3d[yo][xo].z-avg3d.z));
							xSS += quick_square(p3d[yo][xo].x);
						}
					}

				slopeyx = (xybar - avg3d.x * avg3d.y) / (xSS/valid - avg3d.x*avg3d.x);
				yint = avg3d.y - slopeyx * avg3d.x;

				if(zvariance <= 2.0 * valid)
				{
					//Floor or ceiling at a constant height from Kinect
					if(avg3d.z < -400 && avg3d.z > -1200)
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
					//r = std::min<int>(std::max<int>(residual_bar*20,0),255);
					
					if(residual_bar <= valid * 225 && sqrt(residual_xbar + residual_ybar)  <= valid * 175)
					{
						r = 0;
						g = 255-std::min<int>(std::max<int>(128+atan(slopeyx)*64,0),255);//std::min<int>(std::max<int>(yint*20+128,0),255);
						b = std::min<int>(std::max<int>(128+atan(slopeyx)*64,0),255);
					}else{
						r = 0x00;
						g = 0x00;
						b = 0x00;
					}
				}
			}

			for(yo = 0; yo < 8; yo++)
			{
				for(xo = 0; xo < 8; xo++)
				{
					frame[y*8+yo][x*8+xo][0] = r;
					frame[y*8+yo][x*8+xo][1] = g;
					frame[y*8+yo][x*8+xo][2] = b;
				}
			}
		}
	}

	return 0;
}

