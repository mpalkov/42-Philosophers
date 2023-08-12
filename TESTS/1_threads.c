#include <stdio.h> //printf
#include <pthread.h> //threads
#include <sys/time.h> //gettimeofday
#include <unistd.h> //usleep

void	*th_routine(void *data)
{
	pthread_t	tid;

	(void)data;	
	tid = pthread_self();
	printf("[%p] routine started\n", tid);
	sleep(1);
	printf("[%p] routine finished\n", tid);
	return (NULL);
}

void	*test_time(void *unused)
{
	(void)unused;
	struct timeval	tp;
	int	i;
	printf("testtime started\n");

	i = 0;
	while (i < 10)
	{
		gettimeofday(&tp, NULL);
		printf("sec: %ld, susec: %d\n", tp.tv_sec, tp.tv_usec);
		sleep(1);
		++i;
	}
	printf("testtime finished\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t	t1;
	pthread_t	t2;
	pthread_t	t3;

	printf("sizeof pthread_t: %lu\nsizeof pointer: %lu\n--------\n\n", sizeof(pthread_t), sizeof(void *));

	pthread_create(&t1, NULL, th_routine, NULL);
	printf("MAIN: created t1 [%p]\n", t1);	
	pthread_create(&t2, NULL, th_routine, NULL);
	printf("MAIN: created t2 [%p]\n", t2);
	
	pthread_create(&t3, NULL, test_time, NULL);
	printf("MAIN: created t3 [%p]\n", t3);
	printf("argc = %d\n", ++argc);

	pthread_join(t3, NULL);
	printf("MAIN: t3 joined[%p]\n", t3);	
	printf("argc = %d\n", ++argc);
	pthread_join(t1, NULL);
	printf("MAIN: t1 joined [%p]\n", t1);
	printf("argc = %d\n", ++argc);
	
	pthread_join(t2, NULL);
	printf("MAIN: t2 joined [%p]\n", t2);
	printf("argc = %d\n", ++argc);
	
	
	return (0);
}