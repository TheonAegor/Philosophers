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
	int				*status;
} t_philosopher;

typedef struct	s_print
{
	int		args[3];
	long	len;
	long	change;
	char	*num;
	char	*time;
	char	*print;
}	t_print;

void			*time_count(void *arg);
void		    *philosopher(void *arg);
void		    create_philosopher(int i, long *time, long *args, pthread_mutex_t **mu);
void		    print_stat(t_philosopher p);
void		    lock_even(t_philosopher *pp);
void		    lock_odd(t_philosopher *pp);
void 			grab_fork_even(t_philosopher **pp);
void 			grab_fork_odd(t_philosopher **pp);
void 			even_action(t_philosopher *pp);
void 			odd_action(t_philosopher *pp);
void 			free_fork_even(t_philosopher **pp);
void 			free_fork_odd(t_philosopher **pp);
long		    ft_atol(const char *str);
int 		    parcer(int argc, char **argv, long (*args)[]);
void		    print_wait(t_philosopher *p, long time_to_wait);
void		    *race_begins(void *arg);
void		    eat(t_philosopher *pp, int *k);
void		    eat2(t_philosopher *pp, int *k);
void		    eat2_rev(t_philosopher *pp, int *k);
char        	*ft_ltoa_base(long long value, int base);
unsigned int    ft_intsize(long long nb, int base);
size_t  		ft_strlen(const char *str);
size_t  		ft_strlcat(char *dst, char *src, size_t destsize);
void    		printer(t_philosopher *phil);
void 			*print_status(void *var);
static void 	make_str(t_print *print);
void 			free_prints(t_print *print);
