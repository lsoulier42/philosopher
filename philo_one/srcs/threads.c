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

void set_philo(t_philo *philosopher, int i, pthread_t cur_thread)
{
	philosopher->alive = 1;
	philosopher->num = i + 1;
	philosopher->tid = cur_thread;
	philosopher->nb_forks_taken = 0;
	philosopher->state = THINK;
	philosopher->last_eat_date = NOT_EATEN_YET;
	philosopher->last_sleep_date = NOT_SLEPT_YET;
}

int init_threads(t_data *philo_data, t_philo *philosophers)
{
	pthread_t	cur_thread;
	int			i;
	int 		create_return;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		philo_data->current_philo = i + 1;
		create_return = pthread_create(&cur_thread, NULL,
			&philo_routine, philo_data);
		if (create_return == -1)
			return (0);
		set_philo(&(philosophers[i]), philo_data->current_philo, cur_thread);
	}
	return (1);
}
