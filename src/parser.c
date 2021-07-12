#include "philo.h"

int	parcer(int argc, char **argv, long **args)
{
	int		i;

	if (argc != 5 && argc != 6)
		return (ER_NUM_ARGS);
	(*args)[NUM] = ft_atol(argv[1]);
	if ((*args)[NUM] == -1)
		return (ER_INCOR_ARG);
	(*args)[DIE] = ft_atol(argv[2]) * 1000;
	if ((*args)[DIE] == -1)
		return (ER_INCOR_ARG);
	(*args)[EAT] = ft_atol(argv[3]) * 1000;
	if ((*args)[EAT] == -1)
		return (ER_INCOR_ARG);
	(*args)[SLEEP] = ft_atol(argv[4]) * 1000;
	if ((*args)[SLEEP] == -1)
		return (ER_INCOR_ARG);
	if (argc == 6)
		(*args)[FINISH] = ft_atol(argv[5]);
	else
		(*args)[FINISH] = -1;
	return (1);
}
