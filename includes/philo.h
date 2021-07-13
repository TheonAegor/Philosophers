/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:07:33 by taegor            #+#    #+#             */
/*   Updated: 2021/07/13 20:19:40 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "pthread.h"
# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "errno.h"
# include <sys/time.h>

# define COMMON_SYMBOLS 8
# define NUM_OF_ARGS 5

enum e_errors {
	ER_NUM_ARGS = -40,
	ER_INCOR_ARG,
};

enum e_args {
	NUM = 0,
	DIE,
	EAT,
	SLEEP,
	FINISH,
};

enum e_states {
	LFORK,
	RFORK,
	DEATH,
	EATING,
	SLEEPING,
	THINKING,
};

typedef struct s_args
{
	long			*args;
	int				*dead;
	long			*time;
}				t_args;

typedef struct s_phil
{
	long			num;
	long			die;
	long			eat;
	long			sleep;
	long			finish;
	long			*time;
	long			*death_time;
	int				*status;
	int				*one_dead;
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
int			parcer(int argc, char **argv, long **args);
//erorrs
int			error_handler(int err);
//utils
long		ft_atol(const char *str);
size_t		ft_strlen(const char *str);
char		*ft_itoa(long num);
//utils2
size_t		ft_strlcat(char *dst, const char *src, size_t size);
void		free_phils(t_phil *phil, pthread_t *pt, \
		pthread_mutex_t *mu, int num);
void		free_all(t_args *all);
void		detach_join(pthread_t *thr);
//philosophers
int			philosopher(t_args *args, long *time);
void		create_philosopher(long *args, long *time, \
		pthread_mutex_t *mu, t_phil *phil);
void		*life_cycle(void *arg);
int			check_philos(t_phil *ps, int num, int *dead);
//phil_itils
void		init_mutexes(pthread_mutex_t **mu, int num);
void		create_phils(t_args *sct, long *time, \
		pthread_mutex_t *mu, t_phil *phil);
void		create_threads(t_phil *phil, pthread_t *phil_threads, int num);
void		free_detach_destroy(t_phil *phil, pthread_t *pt, \
		pthread_mutex_t *mu, t_args *all);
//printer
void		printer(t_phil *p);
//eat
int			 grab_left(t_phil *p);
int			 grab_right(t_phil *p);
int			 release_right(t_phil *p);
int			 release_left(t_phil *p);
int			 go_eat(t_phil *p);
int			 go_sleep(t_phil *p);
int			 go_think(t_phil *p);
//temporary
void		print_args(t_args *args);
//life_cycle_utils
int			choose_path(t_phil *p);

#endif
