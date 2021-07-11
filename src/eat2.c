#include "philo.h"

int	eating_rev(t_phil *p)
{
	pthread_t		race;

	if (p->i % 2 == 0)
		grab_odd(p);
	else
	{
		usleep(300);
		grab_odd(p);
	}
	usleep(p->eat);
	if (*p->status != DEATH)
	{
		*p->status = EATING;
		gettimeofday(p->last_eat, NULL);
		printer(p);
	}
	if (p->i % 2 == 0)
		unlock_odd(p);
	else
		unlock_even(p);
	if (*p->status == DEATH)
		return (0);
	return (1);
}
