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

int		init_philosophers(t_data *philo_data)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		philo = philo_data->philosophers + i;
		philo->num = i + 1;
		philo->state = SLEEP;
		philo->time_to_die = philo_data->time_to_die;
		philo->time_to_eat = philo_data->time_to_eat;
		philo->time_to_sleep = philo_data->time_to_sleep;
		philo->nb_meal_max = philo_data->nb_meal_max;
		left = philo_data->forks + i;
		right = philo_data->forks + philo_data->nb_philo - 1;
		if (i != 0)
			right = philo_data->forks + i - 1;
		philo->first_fork = philo->num % 2 == 0 ? right : left;
		philo->second_fork = philo->num % 2 == 0 ? left : right;
		philo->output = &philo_data->output;
	}
	return (1);
}

int		load_threads(t_data *philo_data)
{
	int			i;
	pthread_t	current_thread;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		if (pthread_create(&current_thread, NULL, &philo_routine,
				philo_data->philosophers + i) != 0)
			return (thread_error(CREATE_THREAD_ERROR) != NULL);
		pthread_detach(current_thread);
	}
	return (1);
}
