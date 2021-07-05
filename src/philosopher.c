#include "philo.h"

int		philosopher(long *args, long *time)
{
	pthread_t		*phil_threads;
	pthread_mutex_t	*mu;
	t_phil			*phil;
	int				i;

	printf("in philosophers\n");

	phil_threads = malloc(sizeof(pthread_t)*args[NUM]);
	mu = malloc(sizeof(pthread_mutex_t)*args[NUM]);
	phil = malloc(sizeof(t_phil)*args[NUM]);
	i = 0;
	while (i < args[NUM])
	{
		pthread_mutex_init(&mu[i], NULL);
		i++;
	}
	i = 0;
	while (i < args[NUM])
	{
		create_philosopher(args, time, i, mu, &phil[i]); 
		pthread_create(&phil_threads[i], NULL, life_cycle, &phil[i]);
		i++;
	}
	i = 0;
	while (i < args[NUM])
	{
		pthread_join(phil_threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < args[NUM])
	{
		pthread_mutex_destroy(&mu[i]);
		i++;
	}
	printf("end of philosopher\n");
	return (1);
}

void		create_philosopher(long	*args, long *time, int i, pthread_mutex_t *mu, t_phil *phil)
{
	phil->num = args[NUM];	
	phil->die = args[DIE];	
	phil->eat = args[EAT];	
	phil->sleep = args[SLEEP];	
	phil->finish = args[FINISH];	
	phil->time = time;	
	phil->status = malloc(sizeof(int));
	*phil->status = THINKING;
	phil->i = i;
	phil->mu = mu;
	printf("Philosopher created\n");
}

void	*life_cycle(void *arg)
{
	t_phil			*p;
	pthread_t		race;
	int				j;

	p = arg;
	pthread_create(&race, NULL, race_begins, p);
	j = 0;
	while (j != p->finish)
	{
		printer(p);
		if (p->finish > 0)
			j++;
	}
}
