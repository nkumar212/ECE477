#include "slopeframe.h"

ComSlopeFrame::ComSlopeFrame() : Command::Command("SlopeFrame")
{
	memset(frame,0,sizeof(Kinect::video_buffer));
}

int ComSlopeFrame::action(IDS* main)
{
	int x,y,xo,yo;
	int xsum, ysum, xbar, ybar, pbar, xcount, ycount, xscount, yscount, pxscount, pyscount;
	int xslope[7], yslope[7];
	uint8_t r,g,b;
	float xslopebar, yslopebar, variance;
	long sum;
	float dist;
	Kinect::depth_buffer* dframe = main->getDepth();
	uint8_t d1, d0;
	uint32_t d;
	float fd;

	float xsbarbar = 0,ysbarbar = 0;

	int bad_superpix = 0, good_superpix = 0;

	if(main->getDepthCount() <= 0)
	{
		std::cerr << "SlopeFrame awaiting depth data" << std::endl;
		return 1;
	}

	for(y = 0; y < 480/8; y++)
	{
		for(x = 0; x < 640/8; x++)
		{
			yslopebar = 0;
			yscount = 0;
			pbar = 0;
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
//						fprintf(stderr," %d", xbar);
						++xcount;
					}
				}
//				fprintf(stderr,"\n");

				if((xcount > 6))
				{
					xbar /= xcount;
					if(pbar != 0 && yscount)
					{
						yslope[yscount] = (pbar - xbar) / (pyscount - yscount);
						yslopebar += yslope[yscount];
//						fprintf(stderr,"%d (%d - %d) / (%d - %d)\n", yslope[yscount], pbar, xbar, pyscount, yscount);
					}
					pbar = xbar;
					pyscount = yscount;
					++yscount;
				}else
					pbar = 0;
			}
			//(stderr,"\n",fd);

			xslopebar = 0;
			xscount = 0;
			pbar = 0;
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
//						fprintf(stderr," %d", ybar);
						++ycount;
					}
				}

				if((ycount > 6))
				{
					ybar /= ycount;
					if(pbar != 0 && xscount > 0)
					{
						xslope[xscount] = (pbar - ybar) / (pxscount - xscount);
						xslopebar += xslope[xscount];
					}
					pbar = ybar;
					pxscount = xscount;
					++xscount;
				}else
					pbar = 0;

			}
			//(stderr,"\n",fd);

			if(xscount >= 5 && yscount >= 5)
			{
				yslopebar /= yscount;
				xslopebar /= xscount;

				xsbarbar += xslopebar;
				ysbarbar += yslopebar;

				for(yo = 0; yo < yscount; yo++)
					variance += pow(yslope[yo] - yslopebar,2.0) / yscount;

				for(xo = 0; xo < xscount; xo++)
					variance += pow(xslope[xo] - xslopebar,2.0) / xscount;

				r = std::max<float>(std::min<float>((xslopebar*20 + 128),(float)255),(float)0.0);
				g = std::max<float>(std::min<float>((yslopebar*20 + 128),(float)255),(float)0.0);
				b = std::max<float>(std::min<float>(sqrt(variance)*15,(float)255),(float)0.0);
				++good_superpix;
			}
			else
			{
				++bad_superpix;
				r = 0x00;
				g = 0xFF;
				b = 0x00;
			}

			for(yo = 0; yo < 8; yo++)
			{
				for(xo = 0; xo < 8; xo++)
				{
					frame[y*8+yo][x*8+xo][0] = r % 256;
					frame[y*8+yo][x*8+xo][1] = g % 256;
					frame[y*8+yo][x*8+xo][2] = b % 256;
				}
			}
		}
	}
	/*fprintf(stderr,"Bad Superpixels: %f%%    %f %f               \n",
			bad_superpix*100.0/640/480*8*8,
			xsbarbar / good_superpix,
			ysbarbar / good_superpix
	);*/
}
