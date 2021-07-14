/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:35 by taegor            #+#    #+#             */
/*   Updated: 2021/07/14 20:41:13 by taegor           ###   ########.fr       */
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
		if (*args->dead == DEATH || *args->have_eaten == args->args[NUM])
			return (0);
	}
}

void	*race_begins(void *arg)
{
	t_phil			*p;
	struct timeval	time2;
	long			change;

	p = arg;
	change = 0;
	while (1)
	{
		gettimeofday(&time2, NULL);
		change = (time2.tv_sec - (*p->last_eat).tv_sec) * 1000000 + \
				 (time2.tv_usec - (*p->last_eat).tv_usec);
		usleep(1);
		if (*p->one_dead == DEATH)
			return (0);
		if (p->die <= change)
		{
			*p->status = DEATH;
			if (*p->who_is_dead == 0)
				*p->who_is_dead = p->i;
			*p->one_dead = DEATH;
			return (0);
		}
	}
}
