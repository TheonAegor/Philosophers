/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 19:51:43 by taegor            #+#    #+#             */
/*   Updated: 2021/07/15 12:47:35 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_left(t_phil *p)
{
	pthread_mutex_lock(&(p->mu[p->i]));
	if (*p->one_dead != DEATH)
		*p->status = LFORK;
	printer(p);
	return (1);
}

int	grab_right(t_phil *p)
{
	if (p->i == p->num - 1)
		pthread_mutex_lock(&(p->mu[0]));
	else
		pthread_mutex_lock(&(p->mu[(p->i) + 1]));
	if (*p->one_dead != DEATH)
		*p->status = RFORK;
	printer(p);
	return (1);
}

int	release_right(t_phil *p)
{
	if (p->i == p->num - 1)
		pthread_mutex_unlock(&(p->mu[0]));
	else
		pthread_mutex_unlock(&(p->mu[(p->i) + 1]));
	return (1);
}

int	release_left(t_phil *p)
{
	pthread_mutex_unlock(&(p->mu[p->i]));
	return (1);
}

int	go_eat(t_phil *p)
{
	grab_left(p);
	grab_right(p);
	if (*p->one_dead != DEATH)
	{
		*p->status = EATING;
		printer(p);
	}
	my_sleep(p->eat);
	gettimeofday(p->last_eat, NULL);
	release_right(p);
	release_left(p);
	return (1);
}
