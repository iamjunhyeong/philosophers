/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:48:44 by junhyeong         #+#    #+#             */
/*   Updated: 2024/09/06 15:09:57 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_arg *arg, int n)
{
	int	i;

	arg->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	i = 0;
	while (i < n)
	{
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
		(*ph_list)[i].eat_count = 0;
		(*ph_list)[i].id = i;
		(*ph_list)[i].arg = arg;
		(*ph_list)[i].last_eat_time = get_time();
		(*ph_list)[i].left = i;
		(*ph_list)[i].right = i - 1;
		if (i == 0)
			(*ph_list)[i].right = n - 1;
		(*ph_list)[i].thread = 0;
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
