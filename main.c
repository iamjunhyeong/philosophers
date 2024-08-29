#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "libft/libft.h"
#define MAX_LEN 200
#define INT_MAX 2147383647

typedef struct s_philo 
{
	pthread_t 	th;
	int			id;
	int			size;
	int			tid;
	int			status;
	long long	last_eat_time;
	t_arg		*arg;
}	t_philo;

typedef struct s_arg
{
	int 			n;
	int 			eat_time;
	int 			sleep_time;
	int				eat_cnt;
	pthread_mutex_t	*mutex_lock;
}	t_arg;

void	mutex_init(pthread_mutex_t *mutex_lock[], int n)
{
	int	i;

	i = 0;
	while (i < n)  {
		mutex_lock[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(&mutex_lock[i], NULL);
		i++;
	}
	mutex_lock[i] = 0;
}

void	philo_init(t_philo *th_list[], int n, t_arg *arg)
{
	int	i;

	i = 0;
	while (i < n)
	{
		th_list[i] = (t_philo *)malloc(sizeof(t_philo));
		memset(th_list[i], 0, sizeof(t_philo));
		th_list[i]->id = i + 1;
		th_list[i]->arg = arg;
		i++;
	}
	th_list[i] = 0;
}

void	ph_init(t_philo *th_list[], t_arg *arg, int argc, char **argv) 
{
	int i;

	arg->n = ft_atoi(argv[1]);
	arg->eat_time = ft_atoi(argv[2]);
	arg->sleep_time = ft_atoi(argv[3]);
	if (argc == 5)
		arg->eat_cnt = ft_atoi(argv[4]);
	else
		arg->eat_cnt = INT_MAX;
	mutex_init(&arg->mutex_lock, arg->n);
}

void *ph_thread(void *arg)
{
	t_philo	*th_list;
	t_arg *arg;

	arg = (t_arg *)arg; 
	th_list = ((t_arg *)arg)->th_list;
	{

	}
}

long long	get_time(void)
{
	struct timeval	mytime;

	if (gettimeofday(&mytime, NULL) == -1)
		return (-1);
	return ((mytime.tv_sec * 1000) + (mytime.tv_usec / 1000));
}

int ph_start(t_philo th_list[], t_arg *arg)
{
	int	i;

	i = 0;
	arg->th_list = &th_list;
	while (i < arg->n)
	{
		th_list[i].last_eat_time = get_time();
		if (pthread_create(&th_list[i].th, NULL, ph_thread, (void *)arg) != 0) {
			perror("create error\n");
			exit(0);
		}
		i++;
	}
	return (1);
}

// 철학자 수, 수명, 밥는데 걸리는 시간, 잠자는 시간, 각 철학자가 최소한 밥을 먹어야 하는 횟수
int main(int argc, char **argv)
{
	t_arg	arg;
	t_philo *th_list;
	int i = 0;

	ph_init(&th_list, &arg, argc, argv);
	philo_init(th_list, arg.n, &arg);
	ph_start(th_list, &arg);
}
