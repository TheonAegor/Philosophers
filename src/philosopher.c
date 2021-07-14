/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:20 by taegor            #+#    #+#             */
/*   Updated: 2021/07/14 17:46:43 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher(t_args *sct, long *time)
{
	pthread_t		*phil_threads;
	pthread_t		print;
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
		printer(&phil[i], &print);
//		usleep(1000000);
//		usleep(args[NUM] * 1000);
		pthread_join(print, NULL);
		free_detach_destroy(phil, phil_threads, mu, sct);
//		usleep(1000000);
		return (0);
	}
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
		usleep(p->eat / 2);
	j = 0;
	while (j != p->finish)
	{
		if (go_think(p, &print) == 0)
			break ;
		if (go_eat(p, &print) == 0)
			break ;
		if (go_sleep(p, &print) == 0)
			break ;
		if (j <= p->finish)
			j++;
	}
	if (j == p->finish)
		*p->have_eaten += 1;
	pthread_join(print, NULL);
	pthread_exit(0);
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
