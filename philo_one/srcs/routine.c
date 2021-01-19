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
	print_state(philo->num, philo->state);
}

void 	philo_routine_sleep(t_philo *philo)
{
	philo->state = SLEEP;
	philo->last_sleep_date = get_current_timestamp();
	print_state(philo->num, philo->state);
}

void 	philo_routine_eat(t_philo *philo)
{
	take_forks(philo);
	if (philo->nb_forks_taken == 2)
	{
		philo->state = EAT;
		philo->last_eat_date = get_current_timestamp();
		*(philo->meal_taken_ptr) += 1;
		print_state(philo->num, philo->state);
		leave_forks(philo);
	}
}

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo*)philo_void;
	while (!(*(philo->someone_died_ptr))
		&& (*(philo->meal_taken_ptr) < philo->nb_meal_max
		|| philo->nb_meal_max == UNLIMITED_MEAL))
	{
		if ((philo->last_eat_date == NOT_EATEN_YET
			|| philo->time_to_eat > get_current_timestamp() - philo->last_eat_date)
			&& (philo->state == THINK || philo->state == NONE))
			philo_routine_eat(philo);
		else if ((philo->last_sleep_date == NOT_SLEPT_YET
			|| philo->time_to_sleep > get_current_timestamp() - philo->last_sleep_date)
			&& (philo->state == EAT || philo->state == NONE))
			philo_routine_sleep(philo);
		else if ((philo->state == SLEEP || philo->state == NONE))
			philo_routine_think(philo);
		if (philo->last_eat_date != NOT_EATEN_YET
			&& get_current_timestamp() - philo->last_eat_date > philo->time_to_die)
		{
			philo->state = DEAD;
			*(philo->someone_died_ptr) = 1;
		}
	}
	return (NULL);
}
