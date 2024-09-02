/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeong <junhyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:10:29 by junhyeong         #+#    #+#             */
/*   Updated: 2024/09/02 17:35:37 by junhyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define SEC 1000000

typedef struct s_arg
{
	int 						n;
	int 						eat_time;
	int 						sleep_time;
	int							life_time;
	int							eat_cnt;
	int							finish;
	int							finished_eat;
	long long				start_time;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t mutex_print;
	pthread_mutex_t mutex_time;
}	t_arg;

typedef struct s_philo 
{
	pthread_t	thread;
	long long	last_eat_time;
	int				id;
	int				eat_count;
	int				left;
	int				right;
	t_arg		*arg;
}	t_philo;

void time_running(long long running_time, t_arg *arg)
{
	long long	start;
	long long	now;
	
	start = get_time();
	while (!arg->finish)
	{
		now = get_time();
		if (now - start >= running_time)
			break;
		usleep(100);
	}
}

void	wait_to_eat(t_arg *arg)
{
	struct timeval get_time;
	struct timeval timestamp;
	int time_taken;

	gettimeofday(&get_time, NULL);  // 현재 시간을 'get_time'에 저장
	while (1)
	{
			gettimeofday(&timestamp, NULL);  // 현재 시간을 'timestamp'에 저장
			time_taken = timestamp.tv_usec - get_time.tv_usec + \
					(timestamp.tv_sec - get_time.tv_sec) * 1000000;  // 경과 시간(마이크로초 단위) 계산
			if (time_taken > arg->eat_time * 900)  // 경과 시간이 'time_to_eat'의 90%를 초과하는지 확인
					break;  // 조건이 만족되면 반복문 종료
			usleep(arg->eat_time);  // 'time_to_eat' 동안 대기
	}
}

void	mutex_init(t_arg *arg, int n)
{
	int	i;

	arg->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	i = 0;
	while (i < n)  {
		pthread_mutex_init(&(arg->mutex_fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&arg->mutex_print, NULL);
	pthread_mutex_init(&arg->mutex_time, NULL);
}

void	philo_init(t_philo **ph_list, int n, t_arg *arg)
{
	int	i;

	i = 0;
	
	*ph_list = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!(*ph_list))
		exit(0);
	while (i < n)
	{
		(* ph_list)[i].eat_count = 0;
		(* ph_list)[i].id = i;
		(* ph_list)[i].arg = arg;
		(* ph_list)[i].last_eat_time = get_time();
		(* ph_list)[i].left= i;
		(* ph_list)[i].right = i - 1;
		if (i == 0)
			(* ph_list)[i].right = n - 1;
		(* ph_list)[i].thread = 0;
		i++;
	}
}

void	arg_init(t_arg *arg, int argc, char **argv) 
{
	arg->n = ft_atoi(argv[1]);
	arg->life_time = ft_atoi(argv[2]);
	arg->eat_time = ft_atoi(argv[3]);
	arg->sleep_time = ft_atoi(argv[4]);
	arg->eat_cnt = 0; 
	if (argc == 6)
		arg->eat_cnt = ft_atoi(argv[5]);
	arg->finish = 0;
	arg->start_time = get_time();
	arg->finished_eat = 0;
	
}

void	ph_eating(t_philo *philo, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(mutex);
	philo->eat_count++;
}

int ph_print(t_arg *arg, int id, char *msg, int died)
{
	long long	now;

	pthread_mutex_lock(&arg->mutex_print);
	now = get_time();
	if (now == -1)
		exit(0);
	if (!(arg->finish))
		printf("%lld %d %s\n", now - arg->start_time, id, msg);
	if (died)
		return (0);	
	pthread_mutex_unlock(&arg->mutex_print);
	return 0;
}

void	ph_action(t_arg *arg, t_philo *philo)
{
	pthread_mutex_lock(&arg->mutex_fork[philo->left]);
	if (arg->n != 1)
	{
		pthread_mutex_lock(&arg->mutex_fork[philo->right]);
		philo->last_eat_time = get_time();
		ph_print(arg, philo->id + 1, "has taken a fork", 0);
		ph_print(arg, philo->id + 1, "is eating", 0);
		ph_eating(philo, &arg->mutex_time);
		// pthread_mutex_lock(&arg->mutex_time);
		// philo->last_eat_time = get_time();
		// pthread_mutex_unlock(&arg->mutex_time);
		// philo->eat_count++;
		time_running(arg->eat_time, arg);
		pthread_mutex_unlock(&arg->mutex_fork[philo->right]);
	}
	pthread_mutex_unlock(&arg->mutex_fork[philo->left]);
}

void *ph_thread(void *ph)
{
	t_philo	*philo;
	t_arg		*arg;

	philo = (t_philo *)ph;
	arg = philo->arg;
	if ((philo->id + 1) % 2 == 0) {
		wait_to_eat(arg);
	}
	while (!arg->finish)
	{
		// if (arg->n - 1 == philo->id && philo->eat_count == 0)
		// 	usleep(1);
		ph_action(arg, philo);
		if (arg->n == 1)
			time_running(arg->sleep_time, arg);
		if (arg->eat_cnt == philo->eat_count)
		{
			arg->finished_eat++;
			break;
		}
		ph_print(arg, philo->id + 1, "is sleeping", 0);
		time_running(arg->sleep_time, arg);
		ph_print(arg, philo->id + 1, "is thinking", 0);
	}
	return (0);
}

void	ph_check(t_arg *arg, t_philo *ph_list)
{
	int	i;
	long long	now;
	
	while (!arg->finish)
	{
		if ((arg->eat_time != 0) && (arg->n == arg->finished_eat))	
		{
			printf("============ finished ============\n");
			arg->finish = 1;
			break ;
		}
		i = 0;
		while (i < arg->n)
		{
			now = get_time();
			if ((now - ph_list[i].last_eat_time) >= arg->life_time)
			{
				printf("============ died============\n");
				ph_print(arg, i + 1, "died", 1);
				arg->finish = 1;
				pthread_mutex_unlock(&arg->mutex_print);
				break ;
			}
			i++;
		}
	}
}

void	ph_end(t_arg *arg, t_philo *ph_list)
{
	int	i;

	i = 0;
	while (i < arg->n)
	{
		pthread_join(ph_list[i].thread, NULL);
		i++;
	}
}

int ph_start(t_philo *ph_list, t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->n)
	{
		ph_list[i].last_eat_time = get_time();
		if (pthread_create(&ph_list[i].thread, NULL, ph_thread, (void *)&ph_list[i]) != 0) {
			perror("create error\n");
			exit(0);
		}
		i++;
	}
	ph_check(arg, ph_list);
	ph_end(arg, ph_list);
	return (1);
}

// 철학자 수, 수명, 밥는데 걸리는 시간, 잠자는 시간, 각 철학자가 최소한 밥을 먹어야 하는 횟수
int main(int argc, char **argv)
{
	t_arg	arg;
	t_philo *ph_list;

	memset(&arg, 0, sizeof(t_arg));
	arg_init(&arg, argc, argv);
	mutex_init(&arg, arg.n);
	philo_init(&ph_list, arg.n, &arg);
	ph_start(ph_list, &arg);
	return (0);
}
