/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:09:03 by taegor            #+#    #+#             */
/*   Updated: 2021/07/13 15:09:04 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 10 + str[i] - '0';
		else
			return (-1);
	}
	return (res);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

static int	ft_find_tens(long n)
{
	int				i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	if (n == 0 && i == 0)
		i = 1;
	return (i);
}

static char	*ft_ifbigger(char *p, int tens, long long int n)
{
	p = malloc(sizeof(char) * (tens + 1));
	if (!p)
		return (NULL);
	p[tens--] = '\0';
	while (tens >= 0)
	{
		p[tens] = n % 10 + 48;
		n /= 10;
		tens--;
	}
	return (p);
}

char	*ft_itoa(long num)
{
	char			*p;
	int				tens;
	long long int	n;

	p = NULL;
	n = (long int)num;
	tens = ft_find_tens(n);
	if (n >= 0)
		p = ft_ifbigger(p, tens, n);
	else
	{
		p = malloc(sizeof(char) * (tens + 2));
		tens += 1;
		n = (-1) * n;
		p[tens--] = '\0';
		while (tens > 0)
		{
			p[tens] = n % 10 + 48;
			n /= 10;
			tens--;
		}
		p[tens] = '-';
	}
	return (p);
}
