/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:27:53 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/19 10:28:01 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	philo_loop(t_data *philo_data)
{
	int	i;
	int	j;
	int is_finish;

	i = -1;
	is_finish = 1;
	while (++i < philo_data->nb_philo)
	{
		if (philo_data->philosophers[i].state == DEAD)
			return (0);
		j = -1;
		while (++j < philo_data->nb_philo)
		{
			if (philo_data->philosophers[j].nb_meal_max != 0)
				is_finish = 0;
		}
	}
	return (is_finish == 0);
}
