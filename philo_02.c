/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:52:04 by junhyeong         #+#    #+#             */
/*   Updated: 2024/09/06 15:05:54 by junhyeop         ###   ########.fr       */
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

int	ph_print(t_arg *arg, int id, char *msg, int died)
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
	return (0);
}

void	time_running(long long running_time, t_arg *arg)
{
	long long	start;
	long long	now;

	start = get_time();
	while (!arg->finish)
	{
		now = get_time();
		if (now - start >= running_time)
			break ;
		usleep(100);
	}
}

void	wait_to_eat(t_arg *arg)
{
	struct timeval	get_time;
	struct timeval	timestamp;
	int				time_taken;

	gettimeofday(&get_time, NULL);
	while (1)
	{
		gettimeofday(&timestamp, NULL);
		time_taken = timestamp.tv_usec - get_time.tv_usec + \
			(timestamp.tv_sec - get_time.tv_sec) * 1000000;
		if (time_taken > arg->eat_time * 900)
			break ;
		usleep(arg->eat_time);
	}
}
