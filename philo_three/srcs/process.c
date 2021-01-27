/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:00:21 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/25 12:00:29 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int init_philosophers(t_data *philo_data)
{
	int		i;
	t_philo	*current;

	i = -1;
	while(++i < philo_data->nb_philo)
	{
		current = philo_data->philosophers + i;
		current->num = i + 1;
		current->state = SLEEP;
		current->last_eat_date = 0;
		current->last_sleep_date = 0;
		current->start_ts = philo_data->start_ts;
		current->time_to_sleep = philo_data->time_to_sleep;
		current->time_to_die = philo_data->time_to_die;
		current->time_to_eat = philo_data->time_to_eat;
		current->forks = &(philo_data->forks);
		current->nb_meal_max = philo_data->nb_meal_max;
	}
	return (1);
}

int load_process(t_data *philo_data)
{
	int			i;
	pid_t		cpid;

	i = -1;
	while(++i < philo_data->nb_philo)
	{
		cpid = fork();
		if (cpid == 0)
			philo_routine(&(philo_data->philosophers[i]));
		else if (cpid != -1)
			philo_data->process_id[i] = cpid;
		else
			return (0);
	}
	return (1);
}
