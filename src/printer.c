/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:08:42 by taegor            #+#    #+#             */
/*   Updated: 2021/07/13 16:12:05 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_pr(t_print *pr)
{
	free(pr->str);
	free(pr->time);
	free(pr->i);
	free(pr);
}

int		fill_str(t_print *pr, int len)
{
	int	status;

	status = pr->status;
	memset(pr->str, '\0', len);
	ft_strlcat(pr->str, pr->time, len);
	ft_strlcat(pr->str, " ms ", len);
	ft_strlcat(pr->str, pr->i, len);
	ft_strlcat(pr->str, " ", len);
	if (status == DEATH)
		ft_strlcat(pr->str, "died", len);
	else if (status == EATING)
		ft_strlcat(pr->str, "is eating", len);
	else if (status == FORK)
		ft_strlcat(pr->str, "has taken a fork", len);
	else if (status == SLEEPING)
		ft_strlcat(pr->str, "is sleeping", len);
	else if (status == THINKING)
		ft_strlcat(pr->str, "is thinking", len);
	ft_strlcat(pr->str, "\n", len);
	if (write(1, pr->str, len - 1) == -1)
		return (-1);
	return (1);
}

void	*make_str(void *arg)
{
	t_print	*pr;
	int		status;
	int		len;

	pr = arg;
	status = pr->status;
	len = ft_strlen(pr->time) + ft_strlen(pr->i) + COMMON_SYMBOLS;
	if (status == DEATH)
		len += 4;
	else if (status == EATING)
		len += 9;
	else if (status == FORK)
		len += 16;
	else if (status == SLEEPING)
		len += 10;
	else if (status == THINKING)
		len += 11;
	pr->str = malloc(sizeof(char) * len);
	fill_str(pr, len);
	free_pr(pr);
	return (0);
}

void	printer(t_phil *p)
{
	t_print		*pr;
	pthread_t	thr;

	pr = malloc(sizeof(t_print));
	pr->status = *p->status;
	pr->time = ft_itoa(*p->time / 1000);
	pr->i = ft_itoa(p->i);
	pthread_create(&thr, NULL, make_str, pr);
	pthread_detach(thr);
	pthread_join(thr, NULL);
}
