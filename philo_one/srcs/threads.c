/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:04:54 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/24 19:43:28 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	init_philosophers_loop(t_data *philo_data, t_philo *philo, int i)
{
	int	right_fork_id;
	int	left_fork_id;

	philo->state = SLEEP;
	philo->num = i + 1;
	philo->last_eat_date = 0;
	philo->last_sleep_date = 0;
	philo->start_ts = philo_data->start_ts;
	philo->time_to_sleep = philo_data->time_to_sleep;
	philo->time_to_eat = philo_data->time_to_eat;
	philo->nb_meal_max = philo_data->nb_meal_max;
	philo->someone_has_died = &(philo_data->someone_has_died);
	left_fork_id = i;
	right_fork_id = i - 1;
	if (right_fork_id == -1)
	{
		right_fork_id = philo_data->nb_philo - 1;
		if (philo_data->nb_philo == 1)
			right_fork_id = 1;
	}
	philo->forks[LEFT] = &(philo_data->forks[left_fork_id]);
	philo->forks[RIGHT] = &(philo_data->forks[right_fork_id]);
}

void	init_philosophers(t_data *philo_data)
{
	int			i;
	t_philo		*philo;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		philo = &(philo_data->philosophers[i]);
		init_philosophers_loop(philo_data, philo, i);
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
	int	return_value;
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
