#include "philo.h"

int	go_sleep(t_phil *p)
{
	if (*p->one_dead != DEATH)
		*p->status = SLEEPING;
	printer(p);
	my_sleep(p->sleep);
	return (1);
}

int	go_think(t_phil *p)
{
	if (*p->one_dead != DEATH)
		*p->status = THINKING;
	printer(p);
	return (1);
}
