#include "philo.h"

void	print_wait(t_philosopher *p, long time_to_wait)
{
	printer(p);
//	print_stat(*p);
	usleep(time_to_wait);
}

void	*race_begins(void *arg)
{
	t_philosopher	*p;
	struct timeval	time;
	struct timeval	time2;
	long			change;

	p = arg;
	gettimeofday(&time, NULL);
	change = 0;
	while (1)
	{
		gettimeofday(&time2, NULL);
		change = (time2.tv_sec - time.tv_sec)*1000000 + (time2.tv_usec - time.tv_usec); 
		if (p->args[T_DIE] <= change)
		{
			*p->status = DEATH;
			printer(p);
			pthread_exit(NULL);	
			exit(0);
		}
		if(*p->status == EAT)
		{
			pthread_exit(NULL);
			break;
		}
	}
	return (0);
}
