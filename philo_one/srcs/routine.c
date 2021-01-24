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

void	routine_forks(t_philo *philo)
{
	int		first_fork_taken;
	int		second_fork_taken;
	int		first_fork_side;
	int		second_fork_side;

	first_fork_side = philo->num % 2;
	if (philo->forks[first_fork_side]->state == UNLOCKED)
	{
		first_fork_taken = take_a_fork(philo, first_fork_side);
		second_fork_side = first_fork_side == 0;
		second_fork_taken = take_a_fork(philo, second_fork_side);
		if (first_fork_taken && second_fork_taken)
			philo->state = HAS_FORKS;
		else
			leave_forks(philo);
	}
}

void	routine_sleep(t_philo *philo, int ts)
{
	leave_forks(philo);
	philo->state = SLEEP;
	philo->last_sleep_date = ts;
	print_state(ts, philo->num, philo->state);
}

void	routine_eat(t_philo *philo, int ts)
{
	philo->state = EAT;
	philo->last_eat_date = ts;
	philo->nb_meal_max -= 1;
	print_state(ts, philo->num, philo->state);
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
	return (NULL);
}
