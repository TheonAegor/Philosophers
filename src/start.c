#include "philo.h"

int	main(int argc, char *argv[])
{
	pthread_t	time_thread;
	t_args		all;
	long		*time;	
	long		args[5];
	int			err;

	time = malloc(sizeof(long));
	pthread_create(&time_thread, NULL, time_count, time);
	err = parcer(argc, argv, &all.args);
	if (err != 1)
		return (error_handler(err));
	philosopher(all.args, time);
	printf("\nend of main\n");
	return (1);
}
