#include "philo.h"

void	*time_count(void *arg)
{
	struct timeval	time;
	struct timeval	time2;
	t_args			*args;
	long			*change;

	args = arg;
	change = args->time;
	gettimeofday(&time, NULL);
	while (1)
	{
		gettimeofday(&time2, NULL);
		*change = (time2.tv_sec - time.tv_sec) * 1000000 + \
				  (time2.tv_usec - time.tv_usec);
		if (*change < 0)
			*change *= -1;
		if (*args->dead == DEATH)
			return (0);
	}
}

void	*race_begins(void *arg)
{
	t_phil			*p;
	struct timeval	time;
	struct timeval	time2;
	long			change;

	p = arg;
	change = 0;
	while (1)
	{
		time = *p->last_eat;
		gettimeofday(&time2, NULL);
		change = (time2.tv_sec - time.tv_sec) * 1000000 + \
				 (time2.tv_usec - time.tv_usec);
		if (p->die <= change)
		{
			*p->status = DEATH;
			return (0);
		}
//		if (*p->status == SLEEPING)
//			return (0);
	}
}
