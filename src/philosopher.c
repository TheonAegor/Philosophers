#include "philo.h"

int	philosopher(long *args, long *time)
{
	pthread_t		*phil_threads;
	pthread_mutex_t	*mu;
	t_phil			*phil;
	int				i;

	phil_threads = malloc(sizeof(pthread_t) * args[NUM]);
	mu = malloc(sizeof(pthread_mutex_t) * args[NUM]);
	phil = malloc(sizeof(t_phil) * args[NUM]);
	init_mutexes(&mu, args[NUM]);
	create_phils(args, time, mu, phil);
	create_threads(phil, phil_threads, args[NUM]);
	i = check_philos(phil, args[NUM]);
	if (i >= 0)
	{
		printer(&phil[i]);
		free_detach_destroy(phil, phil_threads, mu, args[NUM]);
		usleep(1000);
		return (0);
	}
	return (1);
}

static int	do_cycle(t_phil *p, int *j, pthread_t race)
{
	printer(p);
	if (p->num % 2 == 0)
	{
		if (!(eating(p)))
			return (0);
	}
	else
	{
		if (!(eating_rev(p)))
			return (0);
	}
	if (*p->status == DEATH)
		return (0);
	*p->status = SLEEPING;
	pthread_create(&race, NULL, race_begins, p);
	printer(p);
	usleep(p->sleep);
	*p->death += 1;
	if (p->finish > 0)
		++*j;
	if (*p->status == DEATH)
		return (0);
	*p->status = THINKING;
	return (1);
}

void	*life_cycle(void *arg)
{
	t_phil			*p;
	pthread_t		race;
	int				j;

	p = arg;
	gettimeofday(p->last_eat, NULL);
	pthread_create(&race, NULL, race_begins, p);
	j = 0;
	while (j != p->finish)
	{
		if (do_cycle(p, &j, race) == 0)
			return (0);
	}
}

int	check_flags(int *flags, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (flags[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_philos(t_phil *ps, int num)
{
	int	i;
	int	*flags;

	flags = malloc(sizeof(int) * num);
	while (1)
	{
		i = 0;
		while (i < num)
		{
			if (*ps[i].status == DEATH)
				return (i);
			if (*ps[i].death == ps[i].finish)
				flags[i] = 1;
			if (check_flags(flags, num) == 1)
				return (i);
			i++;
		}
	}	
	return (0);
}
