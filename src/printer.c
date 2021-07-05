#include "philo.h"

void	printer(t_phil *p)
{
	printf("%ld ms, phil %d is %d\n", *p->time / 1000, p->i, *p->status);
}
