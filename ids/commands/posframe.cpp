#include "posframe.h"

float avg_center_y = 0;
int it_counter = 0;

inline float quick_square(float x)
{
	return x*x;
}

ComPosFrame::ComPosFrame(int xyzflags) : ComFrame::ComFrame("PosFrame")
{
	this->xyzflags = xyzflags;
	memset(frame,0,sizeof(Kinect::video_buffer));
}

int ComPosFrame::action(IDS* main)
{
	int x,y,xo,yo;
	Kinect::depth_buffer* dframe = main->getDepth();
	Kinect* kinect = main->getKinect();

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
		std::cerr << "PosFrame awaiting depth data" << std::endl;
		return 1;
	}

	for(y = 0; y < 480/8; y++)
	{
		for(x = 0; x < 640/8; x++)
		{
			avg3d.x = 0;
			avg3d.y = 0;
			avg3d.z = 0;
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
//						fd = 3480*254/(1091.5-(float)d);
//						fd = 4755.3*256/(1091.5-(float)d);
						fd = (-45.7768687166*log(1028-d)+295.5003224073)*100;
						p3d[yo][xo].x = kinect->x3d(x,y,xo,yo,fd);
						p3d[yo][xo].y = kinect->y3d(x,y,xo,yo,fd);
						p3d[yo][xo].z = kinect->z3d(x,y,xo,yo,fd);
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
				b = 0x00;
			}else{

				if((x == 640/8/2 || x==640/8/2+1) && (y==480/8/2||y==480/8/2+1))
				{
					avg_center_y += avg3d.y/4;
					r = 0xFF;
					g = b = 0;
				}else{
					if(xyzflags & X) r = avg3d.x + 128;
					else r = 0;

					if(xyzflags & Y) g = avg3d.y + 128;
					else g = 0;

					if(xyzflags & Z) b = avg3d.z/2 + 128;
					else b = 0;
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

	std::cerr << "Center Distance: " << avg_center_y / ++it_counter << std::endl;

	return 0;
}

