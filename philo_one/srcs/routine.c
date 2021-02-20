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

void	routine_eat(t_philo *philo)
{
	int first_fork;
	int second_fork;

	first_fork = philo->num % 2 == 0 ? RIGHT : LEFT;
	second_fork = first_fork == RIGHT ? LEFT : RIGHT;
	if (pthread_mutex_lock(philo->forks[first_fork]) == 0
		&& pthread_mutex_lock(philo->forks[second_fork]) == 0)
	{
		philo->state = EAT;
		philo->last_eat_date = get_timestamp(philo->start_ts);
		print_state(philo, 0);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->forks[LEFT]);
		pthread_mutex_unlock(philo->forks[RIGHT]);
		philo->nb_meal += 1;
	}
}

void	*philo_routine(void *philo_void)
{
	t_philo		*philo;

	philo = (t_philo*)philo_void;
	philo->start_ts = get_timestamp(0);
	while (!(philo->is_finished))
	{
		if (philo->state == THINK)
			routine_eat(philo);
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
		philo->is_finished = philo->state == DEAD
			|| philo->nb_meal >= philo->nb_meal_max;
	}
	return (NULL);
}
