#include "philo.h"

int	main(int argc, char *argv[])
{
	pthread_t	time_thread;
	t_args		*all;
	long		*time;	
	int			err;

	all = malloc(sizeof(t_args));
	all->dead = malloc(sizeof(int));
	all->args = malloc(sizeof(long) * 5);
	time = malloc(sizeof(long));
	pthread_create(&time_thread, NULL, time_count, time);
	err = parcer(argc, argv, &all->args);
//	print_args(all);
	if (err != 1)
		return (error_handler(err));
	philosopher(all, time);
	return (1);
}
