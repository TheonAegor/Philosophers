#include "philo.h"

int		parcer(int argc, char **argv, long (*args)[])
{
	int		i;

	printf("inside parser\n");
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
	printf("end of parser\n");
}

long	ft_atol(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = -1;
	while(str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 10 + str[i] - '0';
		else
			return (-1);
	}
	return (res);
}
