#include "philo.h"

int main(int argc, char *argv[])
{
	pthread_t	time_thread;
	long		*time;	
	long		args[5];
	int			err;

	time = malloc(sizeof(long));
	pthread_create(&time_thread, NULL, time_count, time);
	if ((err = parcer(argc, argv, &args)) != 1)
		return (error_handler(err));
	philosopher(args, time);

	printf("\nend of main\n");
	return (1);
}