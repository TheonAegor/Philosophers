#include "philo.h"

void	init_mutexes(pthread_mutex_t **mu, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&(*mu)[i], NULL);
		i++;
	}
}

void	create_phils(long *args, long *time, pthread_mutex_t \
		*mu, t_phil *phil)
{
	int	i;

	i = 0;
	while (i < args[NUM])
	{
		create_philosopher(args, time, mu, &phil[i]);
		phil[i].i = i;
		i++;
	}
}

void	create_threads(t_phil *phil, pthread_t *phil_threads, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_create(&phil_threads[i], NULL, life_cycle, &phil[i]);
		i++;
	}
}

void	create_philosopher(long	*args, long *time, \
		pthread_mutex_t *mu, t_phil *phil)
{
	phil->death = malloc(sizeof(int));
	phil->status = malloc(sizeof(int));
	phil->last_eat = malloc(sizeof(struct timeval));
	phil->one_dead = malloc(sizeof(int));
	gettimeofday(phil->last_eat, NULL);
	*phil->status = THINKING;
	*phil->one_dead = 1; 
	*phil->death = 0;
	phil->num = args[NUM];
	phil->die = args[DIE];
	phil->eat = args[EAT];
	phil->sleep = args[SLEEP];
	phil->finish = args[FINISH];
	phil->time = time;
	phil->mu = mu;
}

void	free_detach_destroy(t_phil *phil, pthread_t *pt, \
		pthread_mutex_t *mu, int num)
{
	int	i;

	i = 0;
	while (i < num)
		pthread_detach(pt[i++]);
	i = 0;
	while (i < num)
		pthread_mutex_destroy(&mu[i++]);
	free_all(phil, pt, mu, num);
}
