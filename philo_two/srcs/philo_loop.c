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
	int ts;

	i = -1;
	is_finish = 1;
	while (++i < philo_data->nb_philo)
	{
		ts = get_timestamp() - philo_data->start_ts;
		if (philo_data->time_to_die < ts - philo_data->philosophers[i].last_eat_date
			&& philo_data->philosophers[i].state != EAT)
		{
			philo_data->philosophers[i].state = DEAD;
			print_state(ts, i + 1, DEAD);
			philo_data->someone_has_died = 1;
			return (0);
		}
		if (philo_data->philosophers[i].nb_meal_max != 0)
			is_finish = 0;
		usleep(100);
	}
	return (is_finish == 0);
}
