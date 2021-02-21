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
	t_philo	*philo;

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
		philo->forks = philo_data->forks;
		philo->output = philo_data->output;
		philo->is_finished = 0;
	}
	return (1);
}

int	load_threads(t_data *philo_data)
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
