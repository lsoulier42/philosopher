/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:02:07 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 12:02:08 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	init_philosophers(t_data *philo_data)
{
	int		i;
	t_philo	*current;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		current = philo_data->philosophers + i;
		current->num = i + 1;
		current->state = SLEEP;
		current->time_to_die = philo_data->time_to_die;
		current->time_to_eat = philo_data->time_to_eat;
		current->time_to_sleep = philo_data->time_to_sleep;
		current->nb_meal_max = philo_data->nb_meal_max;
		current->last_eat_date = 0;
		current->forks = philo_data->forks;
		current->output = philo_data->output;
		current->nb_meal_taken = 0;
	}
	return (1);
}

int	load_processes(t_data *philo_data)
{
	int		i;
	pid_t	cpid;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		cpid = fork();
		if (cpid == 0)
			philo_routine(philo_data->philosophers + i);
		else if (cpid != -1)
			philo_data->philosophers_processes[i] = cpid;
		else
			thread_error(FORK_ERROR);
	}
	return (1);
}

int	delete_processes(t_data *philo_data)
{
	int i;

	i = -1;
	while (++i < philo_data->nb_philo)
		kill(philo_data->philosophers_processes[i], SIGKILL);
	return (0);
}
