
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:07:52 by taegor            #+#    #+#             */
/*   Updated: 2021/07/13 17:25:59 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_odd(t_phil *p)
{
	pthread_mutex_lock(&p->mu[p->i]);
	if (*p->one_dead != DEATH)
	{
		*p->status = FORK;
		printer(p);
	}
	if (p->i == p->num - 1)
		pthread_mutex_lock(&p->mu[0]);
	else
		pthread_mutex_lock(&p->mu[p->i + 1]);
	if (*p->one_dead != DEATH)
	{
		*p->status = FORK;
		printer(p);
	}
	return (1);
}

int	grab_even(t_phil *p)
{
	if (p->i == p->num - 1)
		pthread_mutex_lock(&p->mu[0]);
	else
		pthread_mutex_lock(&p->mu[p->i + 1]);
	if (*p->one_dead != DEATH)
	{
		*p->status = FORK;
		printer(p);
	}
	pthread_mutex_lock(&p->mu[p->i]);
	if (*p->one_dead != DEATH)
	{
		*p->status = FORK;
		printer(p);
	}
	return (1);
}

int	unlock_odd(t_phil *p)
{
	pthread_mutex_unlock(&p->mu[p->i]);
	if (p->i == p->num - 1)
		pthread_mutex_unlock(&p->mu[0]);
	else
		pthread_mutex_unlock(&p->mu[p->i + 1]);
	return (1);
}

int	unlock_even(t_phil *p)
{
	if (p->i == p->num - 1)
		pthread_mutex_unlock(&p->mu[0]);
	else
		pthread_mutex_unlock(&p->mu[p->i + 1]);
	pthread_mutex_unlock(&p->mu[p->i]);
	return (1);
}

int	eating(t_phil *p)
{
	if (*p->one_dead == DEATH)
		return (0);
	if (p->i % 2 == 0)
		grab_even(p);
	else
	{
		usleep(1000);
		grab_odd(p);
	}
	if (*p->one_dead != DEATH)
	{
		*p->status = EATING;
		printer(p);
		usleep(p->eat);
		gettimeofday(p->last_eat, NULL);
	}
	if (p->i % 2 == 0)
		unlock_even(p);
	else
		unlock_odd(p);
	if (*p->one_dead == DEATH)
		return (0);
	return (1);
}
