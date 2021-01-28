/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 09:40:40 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/22 09:40:50 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	init_philosophers(t_data *philo_data)
{
	int			i;
	t_philo		*philo;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		philo = &(philo_data->philosophers[i]);
		philo->num = i + 1;
		philo->state = SLEEP;
		philo->last_eat_date = 0;
		philo->last_sleep_date = 0;
		philo->start_ts = philo_data->start_ts;
		philo->time_to_sleep = philo_data->time_to_sleep;
		philo->time_to_eat = philo_data->time_to_eat;
		philo->nb_meal_max = philo_data->nb_meal_max;
		philo->forks = &(philo_data->forks);
		philo->time_to_die = philo_data->time_to_die;
	}
}

int		load_threads(t_data *philo_data)
{
	int			i;
	int			create_return;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		create_return = pthread_create(&(philo_data->threads[i]), NULL,
			&philo_routine, &(philo_data->philosophers[i]));
		if (create_return == -1)
			return (0);
	}
	return (1);
}

int		delete_philosophers(t_data *philo_data)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (++i < philo_data->nb_philo)
	{
		if (pthread_join(philo_data->threads[i], NULL) != 0)
			error = 1;
	}
	return (error == 0);
}
