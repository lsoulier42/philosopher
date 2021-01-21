/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:59:53 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/19 14:00:03 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	init_forks(t_data *philo_data)
{
	int	i;
	int	return_value;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		return_value = pthread_mutex_init(&(philo_data->forks[i]), NULL);
		if (return_value == -1)
			return (0);
	}
	return (1);
}

int delete_forks(t_data *philo_data)
{
	int i;
	int	return_value;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		return_value = pthread_mutex_destroy(&(philo_data->forks[i]));
		if (return_value == -1)
			return (0);
	}
	return (1);
}

int take_forks(t_philo *philo)
{
	if (philo->left_locked || philo->right_locked)
	{
		leave_forks(philo);
		return (0);
	}
	if (pthread_mutex_lock(philo->left_fork) != 0)
	{
		leave_forks(philo);
		return (0);
	}
	philo->left_locked = 1;
	print_state(get_timestamp() - philo->start_ts, philo->num, HAS_TAKEN_FORK);
	if (pthread_mutex_lock(philo->right_fork) != 0)
	{
		leave_forks(philo);
		return (0);
	}
	philo->right_locked = 1;
	print_state(get_timestamp() - philo->start_ts, philo->num, HAS_TAKEN_FORK);
	return (1);
}

int leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	philo->left_locked = 0;
	pthread_mutex_unlock(philo->right_fork);
	philo->right_locked = 0;
	return (1);
}
