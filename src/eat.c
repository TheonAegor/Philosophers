#include "philo.h"

int	grab_odd(t_phil *p)
{
	pthread_mutex_lock(&p->mu[p->i]);
	*p->status = FORK;
	printer(p);
	if (p->i == p->num - 1)
		pthread_mutex_lock(&p->mu[0]);
	else
		pthread_mutex_lock(&p->mu[p->i + 1]);
	*p->status = FORK;
	printer(p);
	return (1);
}

int	grab_even(t_phil *p)
{
	if (p->i == p->num - 1)
		pthread_mutex_lock(&p->mu[0]);
	else
		pthread_mutex_lock(&p->mu[p->i + 1]);
	*p->status = FORK;
	printer(p);
	pthread_mutex_lock(&p->mu[p->i]);
	*p->status = FORK;
	printer(p);
	return (1);
}

int	unlock_odd(t_phil *p)
{
	pthread_mutex_unlock(&p->mu[p->i]);
	if (p->i == p->num - 1)
		pthread_mutex_unlock(&p->mu[0]);
	else
		pthread_mutex_unlock(&p->mu[p->i + 1]);
	return (1);
}

int	unlock_even(t_phil *p)
{
	if (p->i == p->num - 1)
		pthread_mutex_unlock(&p->mu[0]);
	else
		pthread_mutex_unlock(&p->mu[p->i + 1]);
	pthread_mutex_unlock(&p->mu[p->i]);
	return (1);
}

int	eating(t_phil *p)
{
	pthread_t		race;

	if (p->i % 2 == 0)
		grab_even(p);
	else
	{
		usleep(300);
		grab_odd(p);
	}
	usleep(p->eat);
	if (*p->status != DEATH)
	{
		*p->status = EATING;
		gettimeofday(p->last_eat, NULL);
		printer(p);
	}
	if (p->i % 2 == 0)
		unlock_even(p);
	else
		unlock_odd(p);
	if (*p->status == DEATH)
		return (0);
	return (1);
}
