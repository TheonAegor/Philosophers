#include "philo.h"
/*
void	printer(t_phil *p)
{
	if (*p->status == EATING)
		printf("%ld ms, phil %d is eating\n", *p->time, p->i);
	if (*p->status == FORK)
		printf("%ld ms, phil %d grab a fork\n", *p->time, p->i);
	if (*p->status == DEATH)
		printf("%ld ms, phil %d is dead\n", *p->time, p->i);
	if (*p->status == THINKING)
		printf("%ld ms, phil %d is thinking\n", *p->time, p->i);
	if (*p->status == SLEEPING)
		printf("%ld ms, phil %d is sleeping\n", *p->time, p->i);
}
*/
void	free_pr(t_print *pr)
{
	free(pr->str);
	free(pr->time);
	free(pr->i);
	free(pr);
}

void	fill_str(t_print *pr, int len)
{
	int status;

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
	write(1, pr->str, len - 1);
	free_pr(pr);
}

void	*make_str(void *arg)
{
	t_print *pr;
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
	pr->str = malloc(sizeof(char)*len);
	fill_str(pr, len);
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
//	printf("before make str\n");
	pthread_create(&thr, NULL, make_str, pr);
//	pthread_join(thr, NULL);
//	make_str(pr);
}
