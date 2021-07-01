#include "philo.h"

//pthread_t p[2];
//pthread_mutex_t m[2];

int main(int argc, char *argv[])
{
	long			time;
	pthread_mutex_t *mu;
	pthread_t		thread;
	long 			args[5];
	int				i;
	int				check;


	time = 0;
	pthread_create(&thread, NULL, time_count, &time);
	if ((check = parcer(argc, argv, &args)) < 0)
	{
		printf("herer %d\n", i);
		return (-1);
	}
	i = 0;
	mu = malloc(sizeof(pthread_mutex_t) * args[NUM_PHIL]);
	while ( i < args[NUM_PHIL])
	{
		pthread_mutex_init(&mu[i], NULL);
		create_philosopher(i, &time, args, &mu);
		i++;
	}
	/*
	i = 0;
	while (i < phil->args[NUM_PHIL])
	{
		pthread_join(phil->threads[i], NULL);
		i++;
	}
	*/
	printf("end\n");
	pthread_exit(NULL);
	return (1);
}
/*
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
*/
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
		*change = (time2.tv_usec - time.tv_usec);
		if (*change < 0)
			*change *= -1;
	}

}

	/*
void	print_stat(t_philosopher p)
{
	if (p.status == FORK)
		printf("t:[%ld] phil %d has taken a fork\n", *(p.time), p.i);
	if (p.status == SLEEP)
		printf("t:[%ld] phil %d sleeping\n", *(p.time),p.i);
	if (p.status == EAT)
		printf("t:[%ld] phil %d eating\n", *(p.time),p.i);
	if (p.status == THINK)
		printf("t:[%ld] phil %d thinking\n", *(p.time),p.i);
	if (p.status == DEATH)
	{
		printf("t:[%ld] phil %d is dead\n", *(p.time),p.i);
		exit(0);
	}
}
	*/

