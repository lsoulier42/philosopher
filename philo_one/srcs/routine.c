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

void *routine_death(void *philo_void)
{
	t_philo *philo;

	philo = (t_philo*)philo_void;
	while(*(philo->nb_finished) != philo->nb_philo)
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

void	routine_actually_eat(t_philo *philo)
{
	print_state(philo, 0);
	philo->last_eat_date = get_timestamp(philo->start_ts);
	philo->state = EAT;
	print_state(philo, 0);
	usleep(philo->time_to_eat * 1000);
	if(pthread_mutex_unlock(philo->forks[LEFT]) != 0)
		thread_error(MUTEX_UNLOCK_ERROR);
	if(pthread_mutex_unlock(philo->forks[RIGHT]) != 0)
		thread_error(MUTEX_UNLOCK_ERROR);
}

void	routine_eat(t_philo *philo)
{
	int first_fork;
	int second_fork;

	first_fork = LEFT;
	if (philo->num % 2 == 0)
		first_fork = RIGHT;
	if (pthread_mutex_lock(philo->forks[first_fork]) == 0)
	{
		philo->state = HAS_FORKS;
		print_state(philo, 0);
		second_fork = first_fork + 1;
		if (second_fork == 2)
			second_fork = 0;
		if (pthread_mutex_lock(philo->forks[second_fork]) == 0)
			routine_actually_eat(philo);
		else
			thread_error(MUTEX_LOCK_ERROR);
	}
	else
		thread_error(MUTEX_LOCK_ERROR);
}

void	philo_loop(t_philo *philo, int *nb_meals)
{
	if (philo->state == THINK)
	{
		routine_eat(philo);
		*(nb_meals) += 1;
		if (*nb_meals == philo->nb_meal_max)
		{
			pthread_mutex_lock(philo->output);
			*(philo->nb_finished) += 1;
			pthread_mutex_unlock(philo->output);
		}
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
	usleep(10);
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
	while(*(philo->nb_finished) != philo->nb_philo)
		philo_loop(philo, &nb_meals);
	if (*(philo->nb_finished) == philo->nb_philo)
		if (pthread_mutex_unlock(philo->is_dead) != 0)
			thread_error(MUTEX_UNLOCK_ERROR);
	if (pthread_detach(death) != 0)
		thread_error(DETACH_THREAD_ERROR);
	return (NULL);
}
