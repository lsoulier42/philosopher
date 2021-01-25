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
	int		i;
	int		return_value;
	t_fork	*fork;

	i = -1;
	while (++i < philo_data->nb_forks)
	{
		fork = philo_data->forks + i;
		return_value = pthread_mutex_init(&(fork->mutex_id), NULL);
		if (return_value == -1)
			return (0);
		fork->state = UNLOCKED;
	}
	return (1);
}

int	take_a_fork(t_philo *philo, int side_id)
{
	int				fork_taken;
	pthread_mutex_t	*mid;

	fork_taken = 0;
	if (philo->forks[side_id]->state == UNLOCKED)
	{
		mid = &(philo->forks[side_id]->mutex_id);
		fork_taken = pthread_mutex_lock(mid) == 0;
		if (fork_taken)
		{
			philo->forks[side_id]->state = LOCKED;
			print_state(get_timestamp() - philo->start_ts,
				philo->num, HAS_FORKS);
		}
	}
	return (fork_taken);
}

int	delete_forks(t_data *philo_data)
{
	int		i;
	int		return_value;
	t_fork	*fork;

	i = -1;
	while (++i < philo_data->nb_forks)
	{
		fork = philo_data->forks + i;
		pthread_mutex_unlock(&(fork->mutex_id));
		return_value = pthread_mutex_destroy(&(fork->mutex_id));
		if (return_value == -1)
			return (0);
	}
	return (1);
}

int	leave_forks(t_philo *philo)
{
	if (philo->forks[LEFT]->state == LOCKED)
	{
		pthread_mutex_unlock(&(philo->forks[LEFT]->mutex_id));
		philo->forks[LEFT]->state = UNLOCKED;
	}
	if (philo->forks[RIGHT]->state == LOCKED)
	{
		pthread_mutex_unlock(&(philo->forks[RIGHT]->mutex_id));
		philo->forks[RIGHT]->state = UNLOCKED;
	}
	return (1);
}
