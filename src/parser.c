#include "philo.h"

int		parcer(int argc, char **argv, long (*args)[])
{
	int		i;

	if (argc != 5 && argc != 6)
		return (ER_NUM_ARGS);
	if (((*args)[NUM] = ft_atol(argv[1])) == -1)
		return (ER_INCOR_ARG);
	if (((*args)[DIE] = ft_atol(argv[2]) * 1000) == -1)
		return (ER_INCOR_ARG);
	if (((*args)[EAT] = ft_atol(argv[3]) * 1000)== -1)
		return (ER_INCOR_ARG);
	if (((*args)[SLEEP] = ft_atol(argv[4]) * 1000) == -1)
		return (ER_INCOR_ARG);
	if (argc == 6)
		(*args)[FINISH] = ft_atol(argv[5]);
	else
		(*args)[FINISH] = -1;
	return (1);
}
