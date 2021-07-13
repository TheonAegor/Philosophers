/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:47 by taegor            #+#    #+#             */
/*   Updated: 2021/07/13 16:03:52 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	pthread_t	time_thread;
	t_args		*all;
	int			err;

	all = malloc(sizeof(t_args));
	all->dead = malloc(sizeof(int));
	*all->dead = 0;
	all->args = malloc(sizeof(long) * 5);
	all->time = malloc(sizeof(long));
	pthread_create(&time_thread, NULL, time_count, all);
	err = parcer(argc, argv, &all->args);
	if (err != 1)
		return (error_handler(err));
	philosopher(all, all->time);
	pthread_detach(time_thread);
	pthread_join(time_thread, NULL);
	free(all->dead);
	free(all->time);
	free(all->args);
	free(all);
	return (1);
}
