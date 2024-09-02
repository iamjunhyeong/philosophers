/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeong <junhyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:52:04 by junhyeong         #+#    #+#             */
/*   Updated: 2024/09/02 17:52:25 by junhyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
