#include <pthread.h>
#include <math.h>
#include <time.h>

int64_t timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
	return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
		((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}

void IDS::init_freenect(int g_argc, char* g_argv[])
{
	if (freenect_init(&(kinect->f_ctx), NULL) < 0) {
		fprintf(stderr,"freenect_init() failed\n");
		return 1;
	}
}

int main_synchronous(IDS* ids)
{
	struct timespec start, end;

	while(!ids->quit())
	{
		/*Run at 23.98 Hertz*/
		while(timespecDiff(&end, &start) < 1000000000 / 23.98)
		{
			iwait++;
			usleep(500);
			clock_gettime(CLOCK_MONOTONIC, &end);
		}
	}
}
