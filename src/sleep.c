#include "philo.h"

int		go_sleep(t_phil *p)
{
	if (*p->one_dead == DEATH)
		return (0);
	*p->status = SLEEPING;
	printer(p);
	usleep(p->sleep);
	return (1);
}

int		go_think(t_phil *p)
{
	if (*p->one_dead == DEATH)
		return (0);
	*p->status = THINKING;
	printer(p);
	if (*p->one_dead == DEATH)
		return (0);
	return (1);
}
