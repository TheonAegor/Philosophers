/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:20 by taegor            #+#    #+#             */
/*   Updated: 2021/07/15 14:05:14 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end(t_args *sct, t_phil *phil, \
		pthread_t *phil_threads, pthread_mutex_t *mu)
{
	int				i;

	i = check_philos(sct, phil);
	if (i >= 0)
		printer(&phil[i]);
	pthread_mutex_lock(sct->print);
	my_sleep(100000);
	free_detach_destroy(phil, phil_threads, mu, sct);
}

int	philosopher(t_args *sct, long *time)
{
	pthread_t		*phil_threads;
	pthread_mutex_t	*mu;
	t_phil			*phil;
	long			*args;

	args = sct->args;
	phil_threads = malloc(sizeof(pthread_t) * args[NUM]);
	mu = malloc(sizeof(pthread_mutex_t) * args[NUM]);
	phil = malloc(sizeof(t_phil) * args[NUM]);
	init_mutexes(&mu, args[NUM]);
	create_phils(sct, time, mu, phil);
	create_threads(phil, phil_threads, args[NUM]);
	end(sct, phil, phil_threads, mu);
	return (1);
}

void	*life_cycle(void *arg)
{
	t_phil			*p;
	int				j;

	p = arg;
	gettimeofday(p->last_eat, NULL);
	if (p->i % 2 != 0)
		my_sleep(p->eat / 2);
	j = 0;
	while (j != p->finish)
	{
		go_think(p);
		go_eat(p);
		go_sleep(p);
		if (j <= p->finish)
			j++;
		if (*p->one_dead == DEATH)
			return (0);
	}
	if (j == p->finish)
		*p->have_eaten += 1;
	return (0);
}

int	check_philos(t_args *all, t_phil *philos)
{
	struct timeval	time;
	long			change;
	int				i;

	while (1)
	{
		gettimeofday(&time, NULL);
		i = 0;
		while (i < all->args[NUM])
		{
			change = (time.tv_sec - philos[i].last_eat->tv_sec) * 1000000 + (time.tv_usec - philos[i].last_eat->tv_usec);
			if (*all->have_eaten == all->args[NUM])
				return (ALL_FULL);
			if (change >= all->args[DIE])
			{
				*philos[i].status = DEATH;
				*all->dead = DEATH;
				return (i);
			}
			i++;
		}

	}
	return (-1);
}
