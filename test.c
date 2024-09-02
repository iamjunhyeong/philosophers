#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
# include <time.h>
# include <sys/time.h>


long long	get_time(void)
{
	struct timeval	mytime;

	if (gettimeofday(&mytime, NULL) == -1)
		return (-1);
	printf("sec : %ld\n", mytime.tv_sec);
	printf("usec : %ld\n", mytime.tv_usec);
	return ((mytime.tv_sec * 1000) + (mytime.tv_usec / 1000));
}

// 쓰레드 함수
// 1초를 기다린후 아규먼트^2 을 리턴한다.
void *t_function(void *data)
{
    // char a[100000];
    int num;
	num = *((int *)data);
	printf("Thread Start\n");
    // sleep(5);
	printf("Thread end\n");
	return NULL;
}

int main()
{
    long long cur;

		cur = get_time();
		printf("ans : %lld\n", cur);

		usleep(100);
		long long cur2;
		cur2 = get_time();
		printf("ans : %lld\n", cur2 - cur);
}