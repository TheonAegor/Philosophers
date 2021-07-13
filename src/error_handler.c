/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:05 by taegor            #+#    #+#             */
/*   Updated: 2021/07/13 15:08:06 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handler(int err)
{
	if (err == ER_NUM_ARGS)
		printf("Wrong number of arguments\n");
	if (err == ER_INCOR_ARG)
		printf("Incorrect argument\n");
	return (-1);
}
