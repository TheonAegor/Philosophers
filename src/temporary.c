#include "philo.h"


void	print_args(t_args *args)
{
	int i = 0;

	while (i < NUM_OF_ARGS)
	{
		printf("args[%d] = %ld\n",i,  args->args[i]);
		i++;
	}
	printf("dead = %d\n", *args->dead);
}
