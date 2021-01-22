/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 09:45:30 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/22 09:45:40 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		routine_forks(t_philo *philo)
{
	int		first_fork_taken;
	int		second_fork_taken;

	if (philo->forks->current_nb >= 2)
	{
		first_fork_taken = sem_wait(philo->forks->nb_forks_available) == 0;
		if (first_fork_taken)
		{
			philo->forks->current_nb--;
			print_state(get_timestamp() - philo->start_ts, philo->num, HAS_FORKS);
			if (philo->forks->current_nb >= 1)
			{
				second_fork_taken = sem_wait(philo->forks->nb_forks_available) == 0;
				if (second_fork_taken)
				{
					philo->forks->current_nb--;
					print_state(get_timestamp() - philo->start_ts, philo->num, HAS_FORKS);
					philo->state = HAS_FORKS;
				}
			}
			else
			{
				sem_post(philo->forks->nb_forks_available);
				philo->forks->current_nb++;
			}
		}
	}
}

void		routine_sleep(t_philo *philo, long ts)
{
	if (sem_post(philo->forks->nb_forks_available) == 0)
		philo->forks->current_nb++;
	if (sem_post(philo->forks->nb_forks_available) == 0)
		philo->forks->current_nb++;
	philo->state = SLEEP;
	philo->last_sleep_date = ts;
}

void		routine_eat(t_philo *philo, long ts)
{
	philo->state = EAT;
	philo->last_eat_date = ts;
	philo->nb_meal_max -= 1;
}

static void	philo_routine_loop(t_philo *philo, long ts)
{
	if (philo->state != EAT
		&& (ts - philo->last_eat_date) > philo->time_to_die)
		philo->state = DEAD;
	else if (philo->state == THINK)
		routine_forks(philo);
	else if (philo->state == HAS_FORKS)
		routine_eat(philo, ts);
	else if (philo->state == EAT
			 && philo->time_to_eat < ts - philo->last_eat_date)
		routine_sleep(philo, ts);
	else if (philo->state == SLEEP
			 && philo->time_to_sleep < ts - philo->last_sleep_date)
		philo->state = THINK;
}

void		*philo_routine(void *philo_void)
{
	t_philo	*philo;
	long	ts;
	char	previous_state;

	philo = (t_philo*)philo_void;
	while (philo->state != DEAD && philo->nb_meal_max != 0)
	{
		ts = get_timestamp() - philo->start_ts;
		previous_state = philo->state;
		philo_routine_loop(philo, ts);
		if (philo->state != HAS_FORKS && previous_state != philo->state)
			print_state(ts, philo->num, philo->state);
	}
	return (NULL);
}
