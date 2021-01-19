/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:11:43 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/19 11:11:52 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	take_forks(t_data *philo_data, t_philo *philo, long long timestamp)
{

}

void	*philo_routine(void *philo_data_void)
{
	t_data			*philo_data;
	t_philo			*philo;
	long long		time_since_last_meal;
	long long		timestamp;
	struct timeval	tv;

	philo_data = (t_data*)philo_data_void;
	philo = &(philo_data->philosophers[philo_data->current_philo - 1]);
	while (philo->alive)
	{
		gettimeofday(&tv, NULL);
		timestamp = tv.tv_sec * 1000 + tv.tv_usec;
		if (philo_data->time_to_eat > timestamp - philo->last_eat_date
			&& philo->state != EAT)
		{
			take_forks(philo_data, philo, timestamp);
			if (philo->nb_forks_taken == 2)
			{
				philo->state = EAT;
				philo->last_eat_date = timestamp;
			}
		}
		else if (philo_data->time_to_sleep > timestamp - philo->last_sleep_date
			&& philo->state == EAT)
		{
			leave_forks(philo_data, philo, timestamp);
			philo->state = SLEEP;
			philo->last_sleep_date = timestamp;
		}
		else if (philo->state == SLEEP)
			philo->state = THINK;
		time_since_last_meal = timestamp - philo->last_eat_date;
		if (time_since_last_meal > philo_data->time_to_die)
		{
			philo->alive = 0;
			philo_data->someone_died = 1;
		}
		print_state(philo, timestamp);
	}
	return (NULL);
}