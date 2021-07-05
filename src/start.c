#include "philo.h"

int main(int argc, char *argv[])
{
	pthread_t	time_thread;
	long		time;	

	pthread_create(&time_thread, NULL, time_count, &time);
}
