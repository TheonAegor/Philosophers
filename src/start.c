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
	pthread_join(time_thread, NULL);
	pthread_detach(time_thread);
	free(all->dead);
	free(all->args);
	free(all->time);
	free(all);
	return (1);
}
