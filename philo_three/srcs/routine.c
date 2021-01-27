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

void	routine_forks(t_philo *philo)
{
	if (sem_wait(philo->forks->can_take_a_fork) == 0)
	{
		if (sem_wait(philo->forks->nb_forks_available) == 0)
		{
			print_state(get_timestamp() - philo->start_ts,
				philo->num, HAS_FORKS);
			if (sem_wait(philo->forks->nb_forks_available) == 0)
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

void *routine_death(void *philo_void)
{
	int			ts;
	t_philo 	*philo;

	philo = (t_philo*)philo_void;
	while (philo->state != DEAD)
	{
		ts = get_timestamp() - philo->start_ts;
		if (ts - philo->last_eat_date > philo->time_to_die
			&& philo->state != EAT)
		{
			philo->state = DEAD;
			print_state(ts, philo->num, philo->state);
			sem_post(philo->forks->someone_has_died);
		}
		usleep(100);
	}
	return (NULL);
}

int philo_routine(t_philo *philo)
{
	int			ts;
	pthread_t	death;

	if (pthread_create(&death, NULL, &routine_death, philo) != 0)
		return (0);
	while (philo->state != DEAD && philo->nb_meal_max != 0)
	{
		ts = get_timestamp() - philo->start_ts;
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
		usleep(100);
	}
	return (pthread_join(death, NULL));
}
