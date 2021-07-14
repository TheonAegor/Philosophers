/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:20 by taegor            #+#    #+#             */
/*   Updated: 2021/07/14 20:13:24 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end(t_args *sct, t_phil *phil, \
		pthread_t *phil_threads, pthread_mutex_t *mu)
{
	int				i;
	pthread_t		print;

	i = check_philos(sct);
	if (i >= 0)
	{
		printer(&phil[i], &print);
		pthread_mutex_lock(sct->print);
		pthread_join(print, NULL);
		my_sleep(100000);
		free_detach_destroy(phil, phil_threads, mu, sct);
	}
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
	pthread_t		race;
	pthread_t		print;
	int				j;

	p = arg;
	gettimeofday(p->last_eat, NULL);
	pthread_create(&race, NULL, race_begins, p);
	if (p->i % 2 != 0)
		my_sleep(p->eat / 2);
	j = 0;
	while (j != p->finish)
	{
		go_think(p, &print);
		go_eat(p, &print);
		go_sleep(p, &print);
		if (j <= p->finish)
			j++;
	}
	if (j == p->finish)
		*p->have_eaten += 1;
	while (1)
		usleep(1);
}

int	check_philos(t_args *all)
{
	while (1)
	{
		if (*all->dead == DEATH || *all->have_eaten == all->args[NUM])
			return (*all->who_is_dead);
		usleep(1);
	}
	return (0);
}
