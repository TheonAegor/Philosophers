#include "pthread.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/time.h>

int  x = 0;

void	*func(void *arg)
{
	pthread_mutex_t *mu;
	int i;

	mu = arg;
	pthread_mutex_lock(&mu[0]);
	x += 5;
}

void	*func2(void *arg)
{
	pthread_mutex_t *mu;
	int i;

	mu = arg;
	pthread_mutex_unlock(&mu[0]);
	x += 5;
}

int main(void)
{
	pthread_t th;
	pthread_t th2;
	pthread_mutex_t mu;
	pthread_mutex_t mu2;
	pthread_mutex_t *mus;

	pthread_mutex_init(&mu, NULL);
	pthread_mutex_init(&mu2, NULL);

	mus = malloc(sizeof(pthread_mutex_t)*2);
	mus[0] = mu;
	mus[1] = mu2;
	pthread_create(&th, NULL, func, mus);
	pthread_create(&th, NULL, func, mus);
	pthread_create(&th2, NULL, func2, mus);
	pthread_join(th, NULL);
	pthread_join(th2, NULL);
	printf("x = %d\n", x);
	printf("end of main\n");
}
