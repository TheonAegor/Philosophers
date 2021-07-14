#include "philo.h"

int		go_sleep(t_phil *p, pthread_t *print)
{
	if (*p->one_dead != DEATH)
		*p->status = SLEEPING;
	printer(p, print);
	usleep(p->sleep);
	return (1);
}

int		go_think(t_phil *p, pthread_t *print)
{
	if (*p->one_dead != DEATH)
		*p->status = THINKING;
	printer(p, print);
	return (1);
}
