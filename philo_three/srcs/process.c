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
	int i;

	i = -1;
	while(++i < philo_data->nb_philo)
	{
		philo_data->philosophers[i].num = i + 1;
		philo_data->philosophers[i].state = i % 2 ? SLEEP : THINK;
		philo_data->philosophers[i].last_eat_date = philo_data->start_ts;
		philo_data->philosophers[i].last_sleep_date = philo_data->start_ts;
		philo_data->philosophers[i].forks = &(philo_data->forks);
		philo_data->philosophers[i].nb_meal_max = philo_data->nb_meal_max;
	}
	return (1);
}

int load_process(t_data *philo_data)
{
	int		i;
	pid_t	cpid;

	i = -1;
	while(++i < philo_data->nb_philo)
	{
		cpid = fork();
		if (cpid == 0)
			philo_routine(philo_data, &(philo_data->philosophers[i]));
		else if (cpid != -1)
			philo_data->process[i] = cpid;
		else
			return (0);
	}
	return (1);
}

int delete_philosophers(t_data *philo_data)
{
	int i;

	i = -1;
	while(++i < philo_data->nb_philo)
		kill(philo_data->process[i], SIGTERM);
	return (1);
}
