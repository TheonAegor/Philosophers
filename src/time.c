/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:35 by taegor            #+#    #+#             */
/*   Updated: 2021/07/14 14:34:48 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*time_count(void *arg)
{
	struct timeval	time;
	struct timeval	time2;
	t_args			*args;
	long			*change;

	args = arg;
	change = args->time;
	gettimeofday(&time, NULL);
	while (1)
	{
		gettimeofday(&time2, NULL);
		*change = (time2.tv_sec - time.tv_sec) * 1000000 + \
				  (time2.tv_usec - time.tv_usec);
		if (*change < 0)
			*change *= -1;
		if (*args->dead == DEATH)
			return (0);
	}
}

void	*race_begins(void *arg)
{
	t_phil			*p;
	struct timeval	time;
	struct timeval	time2;
	long			change;

	p = arg;
	change = 0;
	while (1)
	{
		gettimeofday(&time2, NULL);
		time = *p->last_eat;
		change = (time2.tv_sec - time.tv_sec) * 1000000 + \
				 (time2.tv_usec - time.tv_usec);
		if (p->die <= change)
		{
			*p->status = DEATH;
			if (*p->who_is_dead == 0)
				*p->who_is_dead = p->i;
			*p->one_dead = DEATH;
			printf("time = %ld,\ntime2 = %ld,\np->die = %ld,\nchange = %ld\n",time.tv_sec * 1000 + time.tv_usec / 1000,time2.tv_sec * 1000 + time2.tv_usec / 1000, p->die, change);
			return (0);
		}
		if (*p->one_dead == DEATH)
			return (0);
	}
}
