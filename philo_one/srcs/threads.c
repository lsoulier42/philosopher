/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:04:54 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/19 11:05:02 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	init_philosophers(t_data *philo_data)
{
	int			i;
	t_philo 	*philo;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		philo = &(philo_data->philosophers[i]);
		philo->state = i % 3;
		philo->num = i + 1;
		philo->last_eat_date = 0;
		philo->last_sleep_date = 0;
		philo->left_locked = 0;
		philo->right_locked = 0;
		philo->start_ts = philo_data->start_ts;
		philo->time_to_die = philo_data->time_to_die;
		philo->time_to_sleep = philo_data->time_to_sleep;
		philo->time_to_eat = philo_data->time_to_eat;
		philo->nb_meal_max = philo_data->nb_meal_max;
		philo->meal_taken_ptr = &(philo_data->nb_meal_taken);
		philo->someone_died_ptr = &(philo_data->someone_died);
		philo->left_fork = &(philo_data->forks[i]);
		if (i - 1 == -1)
			philo->right_fork = &(philo_data->forks[philo_data->nb_philo - 1]);
		else
			philo->right_fork = &(philo_data->forks[i - 1]);
	}
}

int	load_threads(t_data *philo_data)
{
	pthread_t	cur_thread;
	int			i;
	int 		create_return;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		create_return = pthread_create(&cur_thread, NULL,
			&philo_routine, &(philo_data->philosophers[i]));
		if (create_return == -1)
			return (0);
		philo_data->threads[i] = cur_thread;
	}
	return (1);
}

int	delete_philosophers(t_data *philo_data)
{
	int i;
	int return_value;
	int error;

	i = -1;
	error = 0;
	while (++i < philo_data->nb_philo)
	{
		return_value = pthread_detach(philo_data->threads[i]);
		if (return_value == -1)
		{
			error = 1;
			printf("Error.\nThis thread with tid %ld cannot be detached\n",\
				(long)philo_data->threads[i]);
		}
	}
	return (error == 0);
}
