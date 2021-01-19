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

void set_philo(t_philo *philosopher, pthread_t cur_tid)
{
	static int cur_num = 1;

	philosopher->alive = 1;
	philosopher->num = cur_num++;
	philosopher->tid = cur_tid;
	philosopher->nb_forks_taken = 0;
	philosopher->state = THINK;
	philosopher->last_eat_date = NOT_EATEN_YET;
	philosopher->last_sleep_date = NOT_SLEPT_YET;
}

int init_philosophers(t_data *philo_data, t_philo *philosophers)
{
	pthread_t	cur_thread;
	int			i;
	int 		create_return;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		create_return = pthread_create(&cur_thread, NULL,
			&philo_routine, philo_data);
		if (create_return == -1)
			return (0);
		set_philo(&(philo_data->philosophers[i]), cur_thread);
		usleep(10);
	}
	return (1);
}

int	delete_philosophers(t_philo *philosophers, int nb_philo)
{
	int i;
	int return_value;
	int error;

	i = -1;
	error = 0;
	while (++i < nb_philo)
	{
		return_value = pthread_detach(philosophers[i].tid);
		if (return_value == -1)
		{
			error = 1;
			printf("Error.\nThis thread with tid %ld cannot be detached\n", (long)philosophers[i].tid);
		}
	}
	return (error == 0);
}
