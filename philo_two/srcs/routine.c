/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 09:45:30 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/27 12:01:12 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	routine_forks(t_philo *philo)
{
	if (!(*(philo->someone_has_died))
		&& sem_wait(philo->forks->can_take_a_fork) == 0)
	{
		if (!(*(philo->someone_has_died))
			&& sem_wait(philo->forks->nb_forks_available) == 0)
		{
			print_state(get_timestamp() - philo->start_ts,
				philo->num, HAS_FORKS);
			if (!(*(philo->someone_has_died))
				&& sem_wait(philo->forks->nb_forks_available) == 0)
			{
				print_state(get_timestamp() - philo->start_ts,
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

void	philo_routine_loop(t_philo *philo, int ts)
{
	if (philo->state == THINK)
		routine_forks(philo);
	else if (philo->state == HAS_FORKS)
		routine_eat(philo, ts);
	else if (philo->state == EAT
		&& philo->time_to_eat < ts - philo->last_eat_date)
		routine_sleep(philo, ts);
	else if (philo->state == SLEEP
		&& philo->time_to_sleep < ts - philo->last_sleep_date)
	{
		philo->state = THINK;
		print_state(ts, philo->num, philo->state);
	}
}

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;
	int		ts;

	philo = (t_philo*)philo_void;
	while (philo->state != DEAD && philo->nb_meal_max != 0
		&& !(*(philo->someone_has_died)))
	{
		ts = get_timestamp() - philo->start_ts;
		philo_routine_loop(philo, ts);
		usleep(100);
	}
	return (NULL);
}
