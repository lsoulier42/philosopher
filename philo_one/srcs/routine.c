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

void	*philo_routine(void *philo_data_void)
{
	static int		i = 0;
	t_data			*philo_data;
	t_philo			*philo;

	philo_data = (t_data*)philo_data_void;
	philo = &(philo_data->philosophers[i++]);
	while (philo->alive && !(philo_data->someone_died))
	{
		if ((philo->last_eat_date == NOT_EATEN_YET
			|| philo_data->time_to_eat > get_current_timestamp() - philo->last_eat_date)
			&& philo->state == THINK)
		{
			take_forks(philo_data, philo);
			if (philo->nb_forks_taken == 2)
			{
				philo->state = EAT;
				philo->last_eat_date = get_current_timestamp();
				print_state(philo->num, philo->state);
				leave_forks(philo_data, philo);
			}
		}
		else if ((philo->last_sleep_date == NOT_SLEPT_YET
			|| philo_data->time_to_sleep > get_current_timestamp() - philo->last_sleep_date)
			&& philo->state == EAT)
		{
			philo->state = SLEEP;
			philo->last_sleep_date = get_current_timestamp();
			print_state(philo->num, philo->state);
		}
		else
		{
			philo->state = THINK;
			print_state(philo->num, philo->state);
		}
		if (philo->last_eat_date != NOT_EATEN_YET
			&& get_current_timestamp() - philo->last_eat_date > philo_data->time_to_die)
			philo->alive = 0;
	}
	return (NULL);
}
