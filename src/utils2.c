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

void	free_all(t_phil *phil, pthread_t *pt, pthread_mutex_t *mu)
{
	if (phil)
		free(phil);
	if (pt)
		free(pt);
	if (mu)
		free(mu);
}
