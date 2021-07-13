/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:47 by taegor            #+#    #+#             */
/*   Updated: 2021/07/13 17:31:36 by taegor           ###   ########.fr       */
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
	all->args = malloc(sizeof(long) * NUM_OF_ARGS);
	all->time = malloc(sizeof(long));
	*all->dead = 0;
	pthread_create(&time_thread, NULL, time_count, all);
	pthread_detach(time_thread);
	err = parcer(argc, argv, &all->args);
	if (err != 1)
		return (error_handler(err));
	philosopher(all, all->time);
	pthread_join(time_thread, NULL);
	free_all(all);
	return (1);
}
