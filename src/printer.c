#include "philo.h"

void	printer(t_philosopher *phil)
{
	pthread_t	print_thread;
	t_print		*print;
	
	print = (t_print *)malloc(sizeof(t_print));
	print->args[0] = phil->i;
	print->args[1] = *phil->status;
	print->args[2] = 2;
	print->time = ft_ltoa_base(*phil->time, 10);
	print->num = ft_ltoa_base(print->args[0], 10);
	pthread_create(&print_thread, NULL, print_status, print);
}

void *print_status(void *var)
{
	t_print	*print;

	print = var;
	print->len = (ft_strlen(print->num) + ft_strlen(print->time) + 20);
	if (print->args[1] == FORK)
		print->len  += 18;
	else if (print->args[1] == DEATH)
		print->len  += 5;
	else if (print->args[1] == SLEEP)
		print->len  += 12;
	else if (print->args[1] == EAT)
		print->len  += 10;
	else if (print->args[1] == THINK)
		print->len  += 13;
	print->print = (char *)malloc(print->len  + 1);
	memset(print->print,'\0', print->len );
	make_str(print);
	if (print->args[1] == DEATH)
		exit(0);
	pthread_exit(0);
}

static void make_str(t_print *print)
{
	ft_strlcat(print->print, print->time, print->len);
	ft_strlcat(print->print, " ms : Philosopher ", print->len);
	ft_strlcat(print->print,  print->num, print->len);
	if (print->args[1] == FORK)
		ft_strlcat(print->print, " has taken a fork\n", print->len);
	else if (print->args[1] == DEATH)
		ft_strlcat(print->print, " died\n", print->len);
	else if (print->args[1] == SLEEP)
		ft_strlcat(print->print, " is sleeping\n", print->len);
	else if (print->args[1] == EAT)
		ft_strlcat(print->print, " is eating\n", print->len);
	else if (print->args[1] == THINK)
		ft_strlcat(print->print, " is thinking\n", print->len);
	write(1, print->print,  print->len);
}

void free_prints(t_print *print)
{
	free(print->num);
	free(print->time);
	free(print->print);
	if (print->args[1] == 3)
	{
		free(print);
		exit(0);
	}
	free(print);
}
