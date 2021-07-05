#include "philo.h"

int		parcer(int argc, char **argv, long (*args)[])
{
	int		i;

	if (argc != 5 && argc != 6)
		return (ER_NUM_ARGS);
	if (((*args)[0] = ft_atol(argv[1])) == -1)
		return (ER_INCOR_ARG);
	if (((*args)[1] = ft_atol(argv[2])) == -1)
		return (ER_INCOR_ARG);
	if (((*args)[2] = ft_atol(argv[3]))== -1)
		return (ER_INCOR_ARG);
	if (((*args)[3] = ft_atol(argv[4])) == -1)
		return (ER_INCOR_ARG);
	if (argc == 6)
		(*args)[4] = ft_atol(argv[5]);
	else
		(*args)[4] = -1;
	return (1);
}
