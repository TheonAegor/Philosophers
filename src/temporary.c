/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:52 by taegor            #+#    #+#             */
/*   Updated: 2021/07/13 15:08:54 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_args(t_args *args)
{
	int	i;

	i = 0;
	while (i < NUM_OF_ARGS)
	{
		printf("args[%d] = %ld\n", i, args->args[i]);
		i++;
	}
	printf("dead = %d\n", *args->dead);
}
