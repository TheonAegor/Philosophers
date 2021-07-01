#include "philo.h"

void		create_philosopher(int i, long *time, t_philosopher **phil, pthread_mutex_t *mu)
{
	t_philosopher	*pp;
	pthread_t		thread;

	pp = *phil;
	pp->i = i;
	pp->time = time;
	pp->status = THINK;
	pp->mu = mu;

	printf("create_phil %d\n", pp->i);
	pthread_create(&(pp->threads[i]), NULL, philosopher, pp); 
}

void	*philosopher(void *arg)
{
	t_philosopher	*pp;
	pthread_t		thread;
	int k = 0;

	pp = arg;
//	printf("start philosopher %d\n", pp->i);
	pthread_create(&thread, NULL, race_begins, pp);
	while (k != pp->args[NUM_EAT])
	{
		eat2(pp, &k);
		if (pp->args[4] != NO_VAL)
			k++;
//		eat(pp, &k);
	}
}
