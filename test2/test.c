#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void    *cycle()
{
    int     counter;

    counter = 0;
    while (1)
    {
        printf("%d\n", counter++);
    }
}
int main(int argc, char *argv[])
{
    pthread_t t1;

    pthread_create(&t1, NULL, cycle, NULL);
    pthread_join(t1, NULL);
    return (1);
}

