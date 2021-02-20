/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:07:42 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 00:07:44 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
		current->time_to_eat = philo_data->time_to_eat;
		current->time_to_sleep = philo_data->time_to_sleep;
		current->nb_meal_max = philo_data->nb_meal_max;
		current->nb_meal = 0;
		current->last_eat_date = 0;
		current->forks = philo_data->forks;
		current->output = philo_data->output;
		current->is_finished = 0;
	}
	return (1);
}

int	load_threads(t_data *philo_data)
{
	int i;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		if (pthread_create(philo_data->philosophers_threads + i,
			NULL, &philo_routine, philo_data->philosophers + i) != 0)
		{
			thread_error(CREATE_THREAD_ERROR);
			return (delete_threads(philo_data));
		}
	}
	return (1);
}

int	delete_threads(t_data *philo_data)
{
	int i;

	i = -1;
	while (++i < philo_data->nb_philo)
		pthread_detach(philo_data->philosophers_threads[i]);
	return (0);
}
