/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:22:06 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/22 11:22:33 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	philo_loop(t_data *philo_data)
{
	int	i;
	int is_finish;

	i = -1;
	is_finish = 1;
	while (++i < philo_data->nb_philo)
	{
		if (philo_data->philosophers[i].state == DEAD)
		{
			philo_data->someone_has_died = 1;
			return (0);
		}
		if (philo_data->philosophers[i].nb_meal_max != 0)
			is_finish = 0;
		usleep(100);
	}
	return (is_finish == 0);
}
