/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:40:53 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/25 11:41:02 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	routine_forks(t_data *philo_data, t_philo *philo)
{
	if (sem_wait(philo->forks->can_take_a_fork) == 0)
	{
		if (!(philo_data->someone_has_died)
			&& sem_wait(philo->forks->nb_forks_available) == 0)
		{
			print_state(get_timestamp() - philo_data->start_ts,
				philo->num, HAS_FORKS);
			if (!(philo_data->someone_has_died)
				&& sem_wait(philo->forks->nb_forks_available) == 0)
			{
				print_state(get_timestamp() - philo_data->start_ts,
					philo->num, HAS_FORKS);
				philo->state = HAS_FORKS;
			}
		}
	}
}

void	routine_sleep(t_philo *philo, long ts)
{
	sem_post(philo->forks->nb_forks_available);
	sem_post(philo->forks->nb_forks_available);
	sem_post(philo->forks->can_take_a_fork);
	philo->state = SLEEP;
	philo->last_sleep_date = ts;
	print_state(ts, philo->num, philo->state);
}

void	routine_eat(t_philo *philo, long ts)
{
	philo->state = EAT;
	philo->last_eat_date = ts;
	philo->nb_meal_max -= 1;
	print_state(ts, philo->num, philo->state);
}

int philo_routine(t_data *philo_data, t_philo *philo)
{
	int		ts;

	while (philo->state != DEAD && philo->nb_meal_max != 0)
	{
		ts = get_timestamp() - philo_data->start_ts;
		if (ts - philo->last_eat_date > philo_data->time_to_die)
		{
			philo->state = DEAD;
			print_state(ts, philo->num, philo->state);
		}
		if (philo->state == THINK)
			routine_forks(philo_data, philo);
		else if (philo->state == HAS_FORKS)
			routine_eat(philo, ts);
		else if (philo->state == EAT
			&& philo_data->time_to_eat < ts - philo->last_eat_date)
			routine_sleep(philo, ts);
		else if (philo->state == SLEEP
			&& philo_data->time_to_sleep < ts - philo->last_sleep_date)
		{
			philo->state = THINK;
			print_state(ts, philo->num, philo->state);
		}
		usleep(100);
	}
	delete_data(philo_data);
	exit(0);
}
