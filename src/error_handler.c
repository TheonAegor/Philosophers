#include "philo.h"

int	error_handler(int err)
{
	if (err == ER_NUM_ARGS)
		printf("Wrong number of arguments\n");
	if (err == ER_INCOR_ARG)
		printf("Incorrect argument\n");
	return (-1);
}
