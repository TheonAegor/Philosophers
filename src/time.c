#include "philo.h"

void	*time_count(void *arg)
{
	struct timeval	time;
	struct timeval	time2;
	long			*change;

	change = arg;
	gettimeofday(&time, NULL);
	while(1)
	{
		gettimeofday(&time2, NULL);
		*change = (time2.tv_sec - time.tv_sec)*1000000 + (time2.tv_usec - time.tv_usec);
		if (*change < 0)
			*change *= -1;
	}
}
