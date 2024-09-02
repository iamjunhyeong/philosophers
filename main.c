/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeong <junhyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:10:29 by junhyeong         #+#    #+#             */
/*   Updated: 2024/09/02 17:52:27 by junhyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
