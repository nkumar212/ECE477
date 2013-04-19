#include <iostream>
#include "XnCppWrapper.h"


using namespace xn;
using namespace std;

int main()
{
  XnStatus nRetVal = XN_STATUS_OK;
  
  int bShouldRun = 1;

  Context context;

  // Initialize context object
  nRetVal = context.Init();
  // TODO: check error code

  // Create a DepthGenerator node
  DepthGenerator depth;
  ImageGenerator image;

  nRetVal = depth.Create(context);
  nRetVal = image.Create(context);

  // Make it start generating data
  nRetVal = context.StartGeneratingAll();
  // TODO: check error code

  DepthMetaData depthMD;
  ImageMetaData imageMD;

  // Main loop
  while (bShouldRun)
    {
      // Wait for new data to be available
      nRetVal = context.WaitOneUpdateAll(depth);
      if (nRetVal != XN_STATUS_OK)
	{
	  printf("Failed updating data: %s\n", xnGetStatusString(nRetVal));
	  continue;
	}

      // Take current depth map
      depth.GetMetaData(depthMD);
      image.GetMetaData(imageMD);
      
      cout << "center of frame is " << depthMD(depthMD.XRes() / 2, depthMD.YRes() / 2) << '\n';
      cout << "color at frame center is " << imageMD.Data()[imageMD.XRes() / 2] << '\n';
      cout.flush();
      
      

      // TODO: process depth map
    }

  // Clean-up
  context.Release();

  return(0);
}
