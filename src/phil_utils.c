/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:29 by taegor            #+#    #+#             */
/*   Updated: 2021/07/14 20:28:33 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	create_phils(t_args *sct, long *time, pthread_mutex_t \
		*mu, t_phil *phil)
{
	int	i;

	i = 0;
	while (i < sct->args[NUM])
	{
		create_philosopher(sct->args, time, mu, &phil[i]);
		phil[i].i = i;
		phil[i].one_dead = sct->dead;
		phil[i].who_is_dead = sct->who_is_dead;
		phil[i].have_eaten = sct->have_eaten;
		phil[i].print = sct->print;
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
		pthread_detach(phil_threads[i]);
		i++;
	}
}

void	create_philosopher(long	*args, long *time, \
		pthread_mutex_t *mu, t_phil *phil)
{
	phil->status = malloc(sizeof(int));
	phil->last_eat = malloc(sizeof(struct timeval));
	gettimeofday(phil->last_eat, NULL);
	*phil->status = THINKING;
	phil->num = args[NUM];
	phil->die = args[DIE];
	phil->eat = args[EAT];
	phil->sleep = args[SLEEP];
	phil->finish = args[FINISH];
	phil->time = time;
	phil->mu = mu;
}

void	free_detach_destroy(t_phil *phil, pthread_t *pt, \
		pthread_mutex_t *mu, t_args *all)
{
	int	i;
	int	num;

	num = all->args[NUM];
	i = 0;
	while (i < num)
		pthread_mutex_destroy(&mu[i++]);
	free_phils(phil, pt, mu, num);
}
