/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:02:01 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 12:02:03 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*routine_death(void *philo_void)
{
	t_philo *philo;

	philo = (t_philo*)philo_void;
	while (philo->nb_meal_taken != philo->nb_meal_max)
	{
		if ((philo->time_to_die
			< get_timestamp(philo->start_ts) - philo->last_eat_date)
			&& philo->state != EAT)
		{
			philo->state = DEAD;
			print_state(philo, 1);
			philo->nb_meal_taken = philo->nb_meal_max;
		}
		usleep(10);
	}
	exit(philo->state);
}

void	routine_eat(t_philo *philo)
{
	if (sem_wait(philo->forks) == 0 && sem_wait(philo->forks) == 0)
	{
		philo->state = EAT;
		philo->last_eat_date = get_timestamp(philo->start_ts);
		print_state(philo, 0);
		usleep(philo->time_to_eat * 1000);
		sem_post(philo->forks);
		sem_post(philo->forks);
	}
}

void	philo_loop(t_philo *philo)
{
	if (philo->state == THINK)
	{
		routine_eat(philo);
		philo->nb_meal_taken += 1;
	}
	else if (philo->state == EAT)
	{
		philo->state = SLEEP;
		print_state(philo, 0);
		usleep(philo->time_to_sleep * 1000);
	}
	else if (philo->state == SLEEP)
	{
		philo->state = THINK;
		print_state(philo, 0);
	}
}

int		philo_routine(t_philo *philo)
{
	pthread_t	death;

	philo->start_ts = get_timestamp(0);
	if (pthread_create(&death, NULL, &routine_death, philo) != 0)
		return (thread_error(CREATE_THREAD_ERROR) != NULL);
	while (philo->nb_meal_taken != philo->nb_meal_max)
	{
		philo_loop(philo);
		usleep(10);
	}
	if (pthread_detach(death) != 0)
		thread_error(DETACH_THREAD_ERROR);
	exit(philo->state);
}
