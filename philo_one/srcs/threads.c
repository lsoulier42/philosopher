/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:04:54 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/25 10:29:05 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int 	init_philosophers(t_data *philo_data)
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
		current->forks[LEFT] = philo_data->forks + i;
		current->forks[RIGHT] = philo_data->forks + philo_data->nb_philo - 1;
		if (i != 0)
			current->forks[RIGHT] = philo_data->forks + i - 1;
		current->output = &philo_data->output;
		current->is_dead = &philo_data->is_dead;
		current->nb_finished = &philo_data->nb_finished;
		current->nb_philo = philo_data->nb_philo;
	}
	return (1);
}

int		load_threads(t_data *philo_data)
{
	int i;

	i = -1;
	while(++i < philo_data->nb_philo)
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

int delete_threads(t_data *philo_data)
{
	int i;

	i = -1;
	while(++i < philo_data->nb_philo)
		pthread_detach(philo_data->philosophers_threads[i]);
	return (0);
}
