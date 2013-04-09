#include "slopeframe.h"

ComSlopeFrame::ComSlopeFrame() : Command::Command("SlopeFrame")
{
	frame = (Kinect::video_buffer*)malloc(640*480*3);	
}

int ComSlopeFrame::action(IDS* main)
{
	int x,y,xo,yo;
	int xsum, ysum, xbar, ybar, pbar, xcount, ycount, xscount, yscount;
	int xslope[7], yslope[7];
	uint8_t r,g,b;
	float xslopebar, yslopebar, variance;
	long sum;
	float dist;
	Kinect::depth_buffer* dframe = main->getDepth();
	uint8_t d1, d0;
	uint32_t d;
	float fd;


	for(y = 0; y < 480/8; y++)
	{
		for(x = 0; x < 640/8; x++)
		{
			yslopebar = 0;
			yscount = 0;
			for(yo = 0; yo < 8; yo++)
			{
				xbar = 0;
				xcount = 0;
				for(xo = 0; xo < 8; xo++)
				{

					d0 = (*dframe)[y*8+yo][x*8+xo][0];
					d1 = (*dframe)[y*8+yo][x*8+xo][1];
					d = d1;
					d = d << 8 | d0;

					if(d != 0x07FF)
					{
						fd = 3480*254/(1091.5-(float)d);
						xbar += fd;
						++xcount;
					}
				}
				xbar /= xcount;

				if((yo != 0) && (xcount > 6))
				{
					yslope[yscount] = pbar - xbar;
					yslopebar += yslope[yscount];
					//(stderr,"%d ",yslope[yscount]);
					++yscount;
				}

				pbar = xbar;
			}
			//(stderr,"\n",fd);
			yslopebar /= yscount;

			xslopebar = 0;
			xscount = 0;
			for(xo = 0; xo < 8; xo++)
			{
				ybar = 0;
				ycount = 0;
				for(yo = 0; yo < 8; yo++)
				{
					d0 = (*dframe)[y*8+yo][x*8+xo][0];
					d1 = (*dframe)[y*8+yo][x*8+xo][1];
					d = d1;
					d = d << 8 | d0;

					if(d != 0x07FF)
					{
						fd = 3480*254/(1091.5-(float)d);
						ybar += fd;
						++ycount;
					}
				}
				ybar /= ycount;

				if((xo != 0) && (ycount > 6))
				{
					xslope[xscount] = pbar - ybar;
					xslopebar += xslope[xscount];
					//(stderr,"%d ",xslope[xscount]);
					++xscount;
				}

				pbar = ybar;
			}
			xslopebar /= xscount;
			//(stderr,"\n",fd);

			if(xscount >= 6 && yscount >= 6)
			{
				for(yo = 0; yo < yscount; yo++)
					variance += pow(yslope[yo] - yslopebar,2.0) / yscount;

				for(xo = 0; xo < xscount; xo++)
					variance += pow(xslope[xo] - xslopebar,2.0) / xscount;

				//(stderr,"%d %d %d %d\n", xscount, yscount, xslopebar, yslopebar);

				r = std::min<float>(std::max<float>((xslopebar + 128),(float)255),(float)0.0);
				g = std::min<float>(std::max<float>((yslopebar + 128),(float)255),(float)0.0);
				b = std::min<float>(std::max<float>(sqrt(variance)*15+128,(float)255),(float)0.0);
			}
			else
			{
				r = 0xFF;
				g = 0xFF;
				b = 0xFF;
			}

			for(yo = 0; yo < 8; yo++)
			{
				for(xo = 0; xo < 8; xo++)
				{
					(*frame)[y*8+yo][x*8+xo][0] = r % 255;
					(*frame)[y*8+yo][x*8+xo][1] = g % 255;
					(*frame)[y*8+yo][x*8+xo][2] = b % 255;
				}
			}
		}
	}
}
