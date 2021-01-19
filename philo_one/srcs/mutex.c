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

void	take_forks(t_philo *philo)
{
	int return_value;
	int i;
	int right_taken;
	int left_taken;

	i = -1;
	right_taken = 0;
	left_taken = 0;
	while (++i < 2)
	{
		if (i == 0)
			return_value = pthread_mutex_lock(philo->left_fork);
		else
			return_value = pthread_mutex_lock(philo->right_fork);
		if (return_value == 0)
		{
			if (i == 0)
				left_taken = 1;
			else
				right_taken = 1;
			philo->nb_forks_taken++;
			print_state(philo->num, HAS_TAKEN_FORK);
		}
	}
	if (!left_taken)
		pthread_mutex_unlock(philo->right_fork);
	if (!right_taken)
		pthread_mutex_unlock(philo->left_fork);
}

void	leave_forks(t_philo *philo)
{
	int return_value;
	int i;

	i = -1;
	while (++i < 2)
	{
		if (i == 0)
			return_value = pthread_mutex_unlock(philo->left_fork);
		else
			return_value = pthread_mutex_unlock(philo->right_fork);
		if (return_value != -1)
			philo->nb_forks_taken--;
	}
}
