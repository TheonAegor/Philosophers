/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:57 by taegor            #+#    #+#             */
/*   Updated: 2021/07/14 20:29:26 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lsize;
	size_t	dsize;

	lsize = ft_strlen(dst);
	if (size > lsize)
		dsize = lsize + ft_strlen(src);
	else
		dsize = size + ft_strlen(src);
	if (size > lsize)
	{
		dst += lsize;
		size -= lsize;
		while (*src && size-- > 1)
		{
			*dst++ = *src++;
		}
		*dst = '\0';
	}
	return (dsize);
}

void	free_phils(t_phil *phil, pthread_t *pt, pthread_mutex_t *mu, int num)
{
	int	i;

	i = 0;
	if (phil)
	{
		while (i < num)
		{
			free(phil[i].status);
			free(phil[i].last_eat);
			i++;
		}
		free(phil);
	}
	if (pt)
		free(pt);
	if (mu)
		free(mu);
}

void	free_all(t_args *all)
{
	free(all->print);
	free(all->dead);
	free(all->time);
	free(all->args);
	free(all->who_is_dead);
	free(all->have_eaten);
	free(all);
}

void	my_sleep(long usec)
{
	usleep(usec);
}
