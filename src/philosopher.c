/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:20 by taegor            #+#    #+#             */
/*   Updated: 2021/07/13 16:18:23 by taegor           ###   ########.fr       */
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
	i = check_philos(phil, args[NUM], sct->dead);
	if (i >= 0)
	{
		usleep(1000);
		printer(&phil[i]);
	//	free_detach_destroy(phil, phil_threads, mu, sct);
		usleep(10000);
		return (0);
	}
	return (1);
}

static int	do_cycle(t_phil *p, int *j)
{
	if (*p->one_dead == DEATH)
		return (0);
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
	if (*p->one_dead == DEATH)
		return (0);
	*p->status = SLEEPING;
	printer(p);
	usleep(p->sleep);
	++*p->death;
	if (p->finish > 0)
		++*j;
	if (*p->one_dead == DEATH)
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
		if (do_cycle(p, &j) == 0)
			break ;
	}
	pthread_detach(race);
	pthread_join(race, NULL);
	return (0);
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

int	check_philos(t_phil *ps, int num, int *dead)
{
	int	i;
	int	*flags;

	flags = malloc(sizeof(int) * num);
	while (1)
	{
		i = -1;
		while (++i < num)
		{
			if (*ps[i].status == DEATH)
			{
				*dead = DEATH;
				free(flags);
				return (i);
			}
			if (*ps[i].death == ps[i].finish)
				flags[i] = 1;
			if (check_flags(flags, num) == 1)
			{
				free(flags);
				return (i);
			}
		}
	}	
	return (0);
}
