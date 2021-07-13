/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:07:48 by taegor            #+#    #+#             */
/*   Updated: 2021/07/13 16:46:21 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_rev(t_phil *p)
{
	if (*p->one_dead == DEATH)
		return (0);
	if (p->i % 2 == 0)
		grab_odd(p);
	else
	{
		usleep(1000);
		grab_odd(p);
	}
	if (*p->status != DEATH)
	{
		*p->status = EATING;
		printer(p);
		usleep(p->eat);
		gettimeofday(p->last_eat, NULL);
	}
	unlock_odd(p);
	if (*p->status == DEATH)
		return (0);
	return (1);
}
