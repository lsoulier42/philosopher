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

int delete_mutexes(t_data *philo_data)
{
	int i;

	i = -1;
	while(++i < philo_data->nb_forks)
		pthread_mutex_unlock(philo_data->forks + i);
	i = -1;
	while(++i < philo_data->nb_forks)
	{
		pthread_mutex_unlock(philo_data->forks + i);
		pthread_mutex_destroy(philo_data->forks + i);
	}
	pthread_mutex_destroy(&philo_data->output);
	pthread_mutex_unlock(&philo_data->is_dead);
	pthread_mutex_destroy(&philo_data->is_dead);
	return (0);
}

int init_mutexes(t_data *philo_data)
{
	int i;

	i = -1;
	while(++i < philo_data->nb_forks)
	{
		if (pthread_mutex_init(philo_data->forks + i, NULL) != 0)
		{
			thread_error(MUTEX_INIT_ERROR);
			return (delete_mutexes(philo_data));
		}
	}
	if (pthread_mutex_init(&philo_data->output, NULL) != 0)
	{
		thread_error(MUTEX_INIT_ERROR);
		return (delete_mutexes(philo_data));
	}
	if (pthread_mutex_init(&philo_data->is_dead, NULL) != 0)
	{
		thread_error(MUTEX_INIT_ERROR);
		return (delete_mutexes(philo_data));
	}
	if (pthread_mutex_lock(&philo_data->is_dead) != 0)
		return (thread_error(MUTEX_LOCK_ERROR) != NULL);
	return (1);
}
