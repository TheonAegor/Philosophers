#include "philo.h"

int		go_sleep(t_phil *p, pthread_t *print)
{
	if (*p->one_dead == DEATH)
		return (0);
	*p->status = SLEEPING;
	printer(p, print);
	usleep(p->sleep);
	if (*p->one_dead == DEATH)
		return (0);
	return (1);
}

int		go_think(t_phil *p, pthread_t *print)
{
	if (*p->one_dead == DEATH)
		return (0);
	*p->status = THINKING;
	printer(p, print);
	if (*p->one_dead == DEATH)
		return (0);
	return (1);
}
