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

void 	philo_routine_think(t_philo *philo)
{
	philo->state = THINK;
}

void 	philo_routine_sleep(t_philo *philo, long ts)
{
	leave_forks(philo);
	philo->state = SLEEP;
	philo->last_sleep_date = ts;
	print_state(ts, philo->num, philo->state);
}

void 	philo_routine_eat(t_philo *philo, long ts)
{
	if (take_forks(philo))
	{
		philo->state = EAT;
		philo->last_eat_date = ts;
		*(philo->meal_taken_ptr) += 1;
		print_state(ts, philo->num, philo->state);
	}
	else
		usleep(philo->num * 1000);
}

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;
	long	ts;

	philo = (t_philo*)philo_void;
	while (philo->state != DEAD)
	{
		ts = get_timestamp() - philo->start_ts;
		if (ts - philo->last_eat_date > philo->time_to_die)
		{
			philo->state = DEAD;
		}
		/*if (philo->time_to_eat < ts - philo->last_eat_date && philo->state == THINK)
			philo_routine_eat(philo, ts);
		else if (philo->time_to_sleep < ts - philo->last_sleep_date && philo->state == EAT)
			philo_routine_sleep(philo, ts);
		else if (philo->state == SLEEP)
		{
			philo_routine_think(philo);
			print_state(ts, philo->num, philo->state);
		}*/
	}
	return (NULL);
}
