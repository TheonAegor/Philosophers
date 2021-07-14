/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:20 by taegor            #+#    #+#             */
/*   Updated: 2021/07/14 14:33:01 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher(t_args *sct, long *time)
{
	pthread_t		*phil_threads;
	pthread_mutex_t	*mu;
	t_phil			*phil;
	long			*args;
	int				i;

	args = sct->args;

	phil_threads = malloc(sizeof(pthread_t) * args[NUM]);
	mu = malloc(sizeof(pthread_mutex_t) * args[NUM]);
	phil = malloc(sizeof(t_phil) * args[NUM]);

	init_mutexes(&mu, args[NUM]);
	create_phils(sct, time, mu, phil);
	create_threads(phil, phil_threads, args[NUM]);

	i = check_philos(sct);
	if (i >= 0)
	{
		printer(&phil[i]);
		usleep(100000);
//		usleep(args[NUM] * 1000);
	//	free_detach_destroy(phil, phil_threads, mu, sct);
//		usleep(1000000);
		return (0);
	}
	return (1);
}

void	*life_cycle(void *arg)
{
	t_phil			*p;
	pthread_t		race;
	int				j;

	p = arg;
	pthread_create(&race, NULL, race_begins, p);
	gettimeofday(p->last_eat, NULL);
	j = 0;
	if (p->i % 2 != 0)
		usleep(p->eat / 2);
	while (j != p->finish)
	{
		if (go_think(p) == 0)
			break ;
		if (go_eat(p) == 0)
			break ;
		if (go_sleep(p) == 0)
			break ;
		if (j >= p->finish)
			j++;
	}
	return (0);
}

int	check_philos(t_args *all)
{
	while (1)
	{
		if (*all->dead == DEATH)
			return (*all->who_is_dead);
		usleep(1);
	}
	return (0);
}
