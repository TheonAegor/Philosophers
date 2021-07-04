#include "philo.h"

void		create_philosopher(int i, long *time, long *args, pthread_mutex_t **mu)
{
	t_philosopher	*pp;
	int 			k;

	pp = malloc(sizeof(t_philosopher));
	k = 0;
	while (k < 5)
	{
		pp->args[k] = args[k];
		k++;
	}
	pp->i = i;
	pp->time = time;
	pp->status = malloc(sizeof(int));
	*pp->status = THINK;
	pp->mu = *mu;
	pp->threads = malloc(sizeof(pthread_t));

//	printf("create_phil %d\n", pp->i);
	pthread_create(pp->threads, NULL, philosopher, pp); 
//	pthread_join(*pp->threads, NULL);
}

void	*philosopher(void *arg)
{
	t_philosopher	*pp;
	pthread_t		thread;
	int k = 0;

	pp = arg;
//	printf("start philosopher %d\n", pp->i);
//	pthread_create(&thread, NULL, race_begins, pp);
	while (k != pp->args[NUM_EAT])
	{
		if (pp->args[NUM_PHIL] % 2 == 0)
			eat2(pp, &k);
		else
			eat2_rev(pp, &k);
		if (pp->args[4] != NO_VAL)
			k++;
//		eat(pp, &k);
	}
}
