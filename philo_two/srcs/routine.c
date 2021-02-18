/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:07:37 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 00:07:38 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*routine_death(void *philo_void)
{
	t_philo *philo;

	philo = (t_philo*)philo_void;
	while (*(philo->nb_finished) != philo->nb_philo)
	{
		if ((philo->time_to_die
			< get_timestamp(philo->start_ts) - philo->last_eat_date)
			&& philo->state != EAT)
		{
			philo->state = DEAD;
			if (*(philo->nb_finished) != philo->nb_philo)
			{
				print_state(philo, 1);
				*(philo->nb_finished) = philo->nb_philo;
			}
		}
		usleep(10);
	}
	return (NULL);
}

void	routine_eat(t_philo *philo)
{
	if (sem_wait(philo->forks) == 0 && sem_wait(philo->forks) == 0)
	{
		philo->state = EAT;
		philo->last_eat_date = get_timestamp(philo->start_ts);
		print_state(philo, 0);
		ft_usleep(philo->time_to_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
	}
}

void	philo_loop(t_philo *philo, int *nb_meals)
{
	if (philo->state == THINK)
	{
		routine_eat(philo);
		*(nb_meals) += 1;
		if (*nb_meals == philo->nb_meal_max)
		{
			if (sem_wait(philo->output) == 0)
			{
				*(philo->nb_finished) += 1;
				sem_post(philo->output);
			}
		}
	}
	else if (philo->state == EAT)
	{
		philo->state = SLEEP;
		print_state(philo, 0);
		ft_usleep(philo->time_to_sleep);
	}
	else if (philo->state == SLEEP)
	{
		philo->state = THINK;
		print_state(philo, 0);
	}
}

void	*philo_routine(void *philo_void)
{
	t_philo		*philo;
	pthread_t	death;
	int			nb_meals;

	philo = (t_philo*)philo_void;
	philo->start_ts = get_timestamp(0);
	nb_meals = 0;
	if (pthread_create(&death, NULL, &routine_death, philo) != 0)
		return (thread_error(CREATE_THREAD_ERROR));
	while (*(philo->nb_finished) != philo->nb_philo)
	{
		philo_loop(philo, &nb_meals);
		usleep(10);
	}
	if (*(philo->nb_finished) == philo->nb_philo)
		sem_post(philo->is_dead);
	if (pthread_detach(death) != 0)
		thread_error(DETACH_THREAD_ERROR);
	return (NULL);
}
