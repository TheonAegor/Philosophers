#include "pthread.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include <sys/time.h>

enum errors {
	ER_NUM_ARGS = -40,
	ER_INCOR_ARG,
};

enum args {
	NUM = 0,
	DIE,
	EAT,
	SLEEP,
	FINISH,
};

enum states {
	FORK,
	DEATH,
	EATING,
	SLEEPING,
	THINKING,
};


typedef struct s_phil
{
	long			num;
	long			die;
	long			eat;
	long			sleep;
	long			finish;
	long			*time;
	int				*status;
	int				i;
	pthread_mutex_t	*mu;

}				t_phil;

//time
void		*time_count(void *arg);
void		*race_begins(void *arg);
//parcer
int			parcer(int argc, char **argv, long (*args)[]);
//erorrs
int			error_handler(int err);
//utils
long		ft_atol(const char *str);
//philosophers
int			philosopher(long *args, long *time);
void        create_philosopher(long *args, long *time, int i, pthread_mutex_t *mu, t_phil *phil);
void		*life_cycle(void *arg);
//printer
void		printer(t_phil *p);
