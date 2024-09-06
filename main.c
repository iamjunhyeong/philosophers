/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:10:29 by junhyeong         #+#    #+#             */
/*   Updated: 2024/09/06 15:08:29 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_philo	*ph_list;

	memset(&arg, 0, sizeof(t_arg));
	arg_init(&arg, argc, argv);
	mutex_init(&arg, arg.n);
	philo_init(&ph_list, arg.n, &arg);
	ph_start(ph_list, &arg);
	return (0);
}
