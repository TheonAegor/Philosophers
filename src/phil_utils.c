#include "philo.h"

void	init_mutexes(pthread_mutex_t **mu, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&(*mu)[i], NULL);
		i++;
	}
}

void	create_phils(long *args,long *time,pthread_mutex_t *mu,t_phil *phil, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		create_philosopher(args, time, i, mu, &phil[i]);
		i++;
	}
}

void	create_threads(t_phil *phil, pthread_t *phil_threads, int num)
{
	int i;
	
	i = 0;
	while (i < num)
	{
		pthread_create(&phil_threads[i], NULL, life_cycle, &phil[i]);
		i++;
	}
}

void		create_philosopher(long	*args, long *time, int i, pthread_mutex_t *mu, t_phil *phil)
{
	phil->death = malloc(sizeof(int));
	*phil->death = 0;
	phil->num = args[NUM];
	phil->die = args[DIE];
	phil->eat = args[EAT];
	phil->sleep = args[SLEEP];
	phil->finish = args[FINISH];
	phil->time = time;
	phil->status = malloc(sizeof(int));
//	phil->death_time = malloc(sizeof(long));
//	*phil->death_time = 0;
	phil->last_eat = malloc(sizeof(struct timeval));
	*phil->status = THINKING;
	phil->i = i;
	phil->mu = mu;
	printf("Philosopher created\n");
}
