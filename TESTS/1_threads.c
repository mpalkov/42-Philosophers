#include <stdio.h> //printf
#include <pthread.h> //threads
#include <sys/time.h> //gettimeofday
#include <unistd.h> //usleep

void	*th_routine(void *data)
{
	pthread_t	tid;

	(void)data;	
	tid = pthread_self();
	printf("[%p]\n", tid);
	return (NULL);
}

void	test_time(void)
{
	struct timeval	tp;	
	int	i;

	i = 0;
	while (i < 10)
	{
		gettimeofday(&tp, NULL);
		printf("sec: %ld, susec: %d\n", tp.tv_sec, tp.tv_usec);
		sleep(1);
		++i;
	}
	return ;
}


int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	pthread_t	t3;

	pthread_create(&t1, NULL, th_routine, NULL);
	printf("MAIN: created t1 [%p]\n", t1);	
	pthread_create(&t2, NULL, th_routine, NULL);
	printf("MAIN: created t2 [%p]\n", t2);
	
	pthread_create(&t3, NULL, th_routine, NULL);
	printf("MAIN: created t3 [%p]\n", t3);
	

	printf("MAIN: joining t1 [%p]\n", t1);
	pthread_join(t1, NULL);
	
	printf("MAIN: joining t2 [%p]\n", t2);
	pthread_join(t2, NULL);
	
	printf("MAIN: joining t3 [%p]\n", t3);
	pthread_join(t3, NULL);
	

	return (0);
}