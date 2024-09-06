/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:10:19 by junhyeong         #+#    #+#             */
/*   Updated: 2024/09/06 15:09:09 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_arg
{
	int				n;
	int				eat_time;
	int				sleep_time;
	int				life_time;
	int				eat_cnt;
	int				finish;
	int				finished_eat;
	long long		start_time;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_time;
}	t_arg;

typedef struct s_philo
{
	pthread_t	thread;
	long long	last_eat_time;
	int			id;
	int			eat_count;
	int			left;
	int			right;
	t_arg		*arg;
}	t_philo;

void		mutex_init(t_arg *arg, int n);
void		philo_init(t_philo **ph_list, int n, t_arg *arg);
void		arg_init(t_arg *arg, int argc, char **argv);

void		ph_action(t_arg *arg, t_philo *philo);
void		*ph_thread(void *ph);
void		ph_check(t_arg *arg, t_philo *ph_list);
void		ph_end(t_arg *arg, t_philo *ph_list);
int			ph_start(t_philo *ph_list, t_arg *arg);

void		ph_eating(t_philo *philo, pthread_mutex_t *mutex);
int			ph_print(t_arg *arg, int id, char *msg, int died);
void		time_running(long long running_time, t_arg *arg);
void		wait_to_eat(t_arg *arg);

int			ft_atoi(const char *str);
long long	get_time(void);

#endif