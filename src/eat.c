
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:07:52 by taegor            #+#    #+#             */
/*   Updated: 2021/07/14 18:50:23 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_left(t_phil *p, pthread_t *print)
{
	pthread_mutex_lock(&(p->mu[p->i]));
	if (*p->one_dead != DEATH)
		*p->status = LFORK;
	printer(p, print);
	return (1);
}

int	grab_right(t_phil *p, pthread_t *print)
{
	if (p->i == p->num - 1)
		pthread_mutex_lock(&(p->mu[0]));
	else
		pthread_mutex_lock(&(p->mu[(p->i) + 1]));
	if (*p->one_dead != DEATH)
		*p->status = RFORK;
	printer(p, print);
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

int	go_eat(t_phil *p, pthread_t *print)
{
	//printf("here i = %d, p->num = %d\n", p->i, (int)p->num - 1);
	grab_left(p, print);
	grab_right(p, print);
	if (*p->one_dead != DEATH)
		*p->status = EATING;
	printer(p, print);
	usleep(p->eat);
	gettimeofday(p->last_eat, NULL);
	release_right(p);
	release_left(p);
	return (1);
}
