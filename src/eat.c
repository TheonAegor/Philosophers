#include "philo.h"

void	grab_fork(t_philosopher **pp)
{
	pthread_mutex_lock(&((*pp)->mu[(*pp)->i]));
	(*pp)->status = FORK;
	printer(*pp);
//	print_stat(**pp); 
	if ((*pp)->i == (*pp)->args[NUM_PHIL] - 1)
		pthread_mutex_lock(&((*pp)->mu[0]));
	else
		pthread_mutex_unlock(&((*pp)->mu[(*pp)->i + 1]));
	(*pp)->status = FORK;
	printer(*pp);
//	print_stat(**pp); 
}

void	free_fork(t_philosopher **pp)
{
	pthread_mutex_unlock(&((*pp)->mu[(*pp)->i]));
	if ((*pp)->i == (*pp)->args[NUM_PHIL] - 1)
		pthread_mutex_unlock(&((*pp)->mu[0]));
	else
		pthread_mutex_unlock(&((*pp)->mu[(*pp)->i + 1]));

}

void	eat2(t_philosopher *pp, int *k)
{
	pthread_t	thread;
	
	printer(pp);
//	print_stat(*pp); 
	grab_fork(&pp);

	pp->status = EAT;
	printer(pp);
//	print_stat(*pp); 
	usleep(pp->args[T_EAT]);

	free_fork(&pp);

	pp->status = SLEEP;
	printer(pp);
//	print_stat(*pp); 
	usleep(pp->args[T_SLEEP]);
	
	pthread_create(&thread, NULL, race_begins, pp);
	pp->status = THINK;
}	
/*
void	eat(t_philosopher *pp, int *k)
{
	pthread_t	thread;

	printer(pp);
//	print_stat(*pp); //think
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
	pthread_create(&thread, NULL, race_begins, pp);
}
*/
