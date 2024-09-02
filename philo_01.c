/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeong <junhyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:50:30 by junhyeong         #+#    #+#             */
/*   Updated: 2024/09/02 17:52:03 by junhyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
