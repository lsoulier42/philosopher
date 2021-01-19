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

int	init_forks(pthread_mutex_t *forks, int nb_forks)
{
	int					i;
	int					return_value;

	i = -1;
	while (++i < nb_forks)
	{
		return_value = pthread_mutex_init(&(forks[i]), NULL);
		if (return_value == -1)
			return (0);
	}
	return (1);
}

int delete_forks(pthread_mutex_t *forks, int nb_forks)
{
	int i;
	int	return_value;

	i = -1;
	while (++i < nb_forks)
	{
		return_value = pthread_mutex_destroy(&(forks[i]));
		if (return_value == -1)
			return (0);
	}
	return (1);
}

void 	get_fork_id(int nb_philo, int philo_num, int fork[][2])
{
	(*fork)[LEFT] = philo_num - 1;
	(*fork)[RIGHT] = philo_num - 2;
	if ((*fork)[RIGHT] == -1)
		(*fork)[RIGHT] = nb_philo - 1;
}

void	take_forks(t_data *philo_data, t_philo *philo)
{
	int forks_id[2];
	int return_value;
	int i;

	i = -1;
	get_fork_id(philo_data->nb_philo, philo->num, &forks_id);
	while (++i < 2)
	{
		return_value = pthread_mutex_lock(&(philo_data->forks[forks_id[i]]));
		if (return_value == 0)
		{
			philo->nb_forks_taken++;
			print_state(philo->num, HAS_TAKEN_FORK);
		}
	}
}

void	leave_forks(t_data *philo_data, t_philo *philo)
{
	int forks_id[2];
	int return_value;
	int i;

	i = -1;
	get_fork_id(philo_data->nb_philo, philo->num, &forks_id);
	while (++i < 2)
	{
		return_value = pthread_mutex_unlock(&(philo_data->forks[forks_id[i]]));
		if (return_value != -1)
			philo->nb_forks_taken--;
	}
}
