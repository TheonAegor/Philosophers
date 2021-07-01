#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

//milisecond - одна миллионная секунды
enum states {
	FORK,
	DEATH,
	SLEEP,
	EAT,
	THINK,	
};

enum args {
	NUM_PHIL = 0,
	T_DIE = 1,
	T_EAT = 2,
	T_SLEEP = 3,
	NUM_EAT = 4,
	NO_VAL = -1,
};

enum errors {
	ER_NUM_ARGS = -13,
	ER_INCOR_ARG,
};

typedef struct s_philosopher
{
	long			args[5];
	int				i;
	long			*time;
	pthread_mutex_t	*mu;
	pthread_t		*threads;
	enum states		status;
} t_philosopher;
void	*time_count(void *arg);
void    *philosopher(void *arg);
void        create_philosopher(int i, long *time, t_philosopher **phil, pthread_mutex_t *mu);
void    print_stat(t_philosopher p);
void    lock_even(t_philosopher *pp);
void    lock_odd(t_philosopher *pp);
long    ft_atol(const char *str);
int     parcer(int argc, char **argv, t_philosopher **phil);
void    print_wait(t_philosopher *p, long time_to_wait);

int main(int argc, char *argv[])
{
	long			time;
	t_philosopher	*phil;
	pthread_mutex_t *mu;
	pthread_t		thread;
	int				i;


	time = 0;
	pthread_create(&thread, NULL, time_count, &time);	
	phil = malloc(sizeof(t_philosopher));
	if ((i = parcer(argc, argv, &phil)) < 0)
	{
		printf("herer %d\n", i);
		return (-1);
	}
	i = 0;
	mu = malloc(sizeof(pthread_mutex_t) * phil->args[NUM_PHIL]);
	phil->threads = malloc(sizeof(pthread_t) * phil->args[NUM_PHIL]); 
	while ( i < phil->args[NUM_PHIL])
	{
		//pthread_mutex_init(&m[i], NULL);
		pthread_mutex_init(&mu[i], NULL);
		create_philosopher(i, &time, &phil, mu);
		i++;
	}
	i = 0;
	while (i < phil->args[NUM_PHIL])
	{
		pthread_join(phil->threads[i], NULL);
		i++;
	}
	printf("end\n");
	pthread_exit(NULL);
	return (1);
}

void	lock_even(t_philosopher *pp)
{
	if (pp->i % 2 == 0)
	{
//		printf("t:[%ld] phil %d grab a fork\n", *pp->time);
		pp->status = FORK;
		pthread_mutex_lock(&pp->mu[pp->i]);	
		print_stat(*pp);
		if (pp->i == NUM_PHIL - 1)
			pthread_mutex_lock(&pp->mu[0]);	
		else
			pthread_mutex_lock(&pp->mu[pp->i + 1]);	
		print_stat(*pp);
	}
	else
	{
//		printf("t:[%ld] phil %d grab a fork\n",pp->i, *pp->time);
		pp->status = FORK;
		if (pp->i == NUM_PHIL - 1)
			pthread_mutex_lock(&pp->mu[0]);	
		else
			pthread_mutex_lock(&pp->mu[pp->i + 1]);	
		print_stat(*pp);
		pthread_mutex_lock(&pp->mu[pp->i]);	
		print_stat(*pp);
	}
}

void	lock_odd(t_philosopher *pp)
{
	if (pp->i % 2 != 0)
	{
//		printf("t:[%ld] phil %d grab a fork\n", *pp->time);
		pp->status = FORK;
		pthread_mutex_lock(&pp->mu[pp->i]);	
		print_stat(*pp);
		if (pp->i == NUM_PHIL - 1)
			pthread_mutex_lock(&pp->mu[0]);	
		else
			pthread_mutex_lock(&pp->mu[pp->i + 1]);	
		print_stat(*pp);
	}
	else
	{
//		printf("t:[%ld] phil %d grab a fork\n",pp->i, *pp->time);
		pp->status = FORK;
		if (pp->i == NUM_PHIL - 1)
			pthread_mutex_lock(&pp->mu[0]);	
		else
			pthread_mutex_lock(&pp->mu[pp->i + 1]);	
		print_stat(*pp);
		pthread_mutex_lock(&pp->mu[pp->i]);	
		print_stat(*pp);
	}
}

void	*time_count(void *arg)
{
	struct timeval	time;
	struct timeval	time2;
	long			*change;

	change = arg;
	gettimeofday(&time, NULL);
	while(1)
	{
		gettimeofday(&time2, NULL);
		*change = (((time2.tv_sec - time.tv_sec) * 1000) + ((time2.tv_sec - time.tv_sec) / 1000));
		if (*change < 0)
			*change *= -1;
	}

}

void	print_stat(t_philosopher p)
{
	if (p.status == FORK)
		printf("t:[%ld] phil %d has taken a fork\n", *p.time, p.i);
	if (p.status == SLEEP)
		printf("t:[%ld] phil %d sleeping\n", *p.time,p.i);
	if (p.status == EAT)
		printf("t:[%ld] phil %d eating\n", *p.time,p.i);
	if (p.status == THINK)
		printf("t:[%ld] phil %d thinking\n", *p.time,p.i);
	if (p.status == DEATH)
	{
		printf("t:[%ld] phil %d is dead\n", *p.time,p.i);
		exit(0);
	}
}

int		parcer(int argc, char **argv, t_philosopher **phil)
{
	int		i;

	printf("inside parser\n");
	if (argc != 5 && argc != 6)
		return (ER_NUM_ARGS);
	if (((*phil)->args[0] = ft_atol(argv[1])) == -1)
		return (ER_INCOR_ARG);
	if (((*phil)->args[1] = ft_atol(argv[2])) == -1)
		return (ER_INCOR_ARG);
	if (((*phil)->args[2] = ft_atol(argv[3]))== -1)
		return (ER_INCOR_ARG);
	if (((*phil)->args[3] = ft_atol(argv[4])) == -1)
		return (ER_INCOR_ARG);
	if (argc == 6)
		(*phil)->args[4] = ft_atol(argv[5]);
	else
		(*phil)->args[4] = -1;
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

void		create_philosopher(int i, long *time, t_philosopher **phil, pthread_mutex_t *mu)
{
	t_philosopher	*pp;
	pthread_t		thread;

	pp = *phil;
	pp->i = i;
	pp->time = time;
	pp->status = THINK;
	pp->mu = mu;

	pthread_create(&(pp->threads[i]), NULL, philosopher, pp); 
}

void	*philosopher(void *arg)
{
	t_philosopher	*pp;
	int k = 0;

	pp = arg;
	while (k != pp->args[NUM_EAT])
	{
		print_stat(*pp); //think
		if (pp->args[NUM_PHIL] %2 == 0)
			lock_even(pp);
		else
			lock_odd(pp);
		pp->status = EAT;
		print_wait(pp, pp->args[T_EAT]);
		if (pp->i == pp->args[NUM_PHIL] - 1)
			pthread_mutex_unlock(&(pp->mu[0]));
		else
			pthread_mutex_unlock(&(pp->mu[pp->i + 1]));
		pthread_mutex_unlock(&(pp->mu[pp->i]));
		pp->status = SLEEP;	

		if (pp->args[NUM_EAT] > 0)
			k++;
		print_wait(pp, pp->args[T_SLEEP]);
		pp->status = THINK;
	}
}

void	print_wait(t_philosopher *p, long time_to_wait)
{
	print_stat(*p);
	usleep(time_to_wait);
}