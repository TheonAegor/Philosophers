#include "pthread.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/time.h>

#define COMMON_SYMBOLS 8

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
	int				*death;
	pthread_mutex_t	*mu;
	struct timeval	*last_eat;

}				t_phil;

typedef struct s_print
{
	int			status;
	char		*i;
	char		*time;
	char		*str;
}				t_print;

//time
void		*time_count(void *arg);
void		*race_begins(void *arg);
//parcer
int			parcer(int argc, char **argv, long (*args)[]);
//erorrs
int			error_handler(int err);
//utils
long		ft_atol(const char *str);
size_t		ft_strlen(const char *str);
char        *ft_itoa(long num);
//utils2
size_t      ft_strlcat(char *dst, const char *src, size_t size);
void        free_all(t_phil *phil, pthread_t *pt, pthread_mutex_t *mu);
//philosophers
int			philosopher(long *args, long *time);
void        create_philosopher(long *args, long *time, int i, pthread_mutex_t *mu, t_phil *phil);
void		*life_cycle(void *arg);
int			check_philos(t_phil *ps, int num);
//phil_itils
void		init_mutexes(pthread_mutex_t **mu, int num);
void		create_phils(long *args,long *time,pthread_mutex_t *mu,t_phil *phil, int num);
void		create_threads(t_phil *phil, pthread_t *phil_threads, int num);
//printer
void		printer(t_phil *p);
//eat
int			eating(t_phil *p);
int			eating_rev(t_phil *p);
