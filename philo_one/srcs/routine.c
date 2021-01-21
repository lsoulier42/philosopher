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
	int	first_fork_taken;
	int	second_fork_taken;
	char first_fork_side;

	first_fork_side = philo->num % 2;
	first_fork_taken = take_a_fork(philo, first_fork_side);
	second_fork_taken = take_a_fork(philo, first_fork_side == 0);
	if (first_fork_taken && second_fork_taken)
		philo->state = HAS_FORKS;
	else
		leave_forks(philo);
}

void 	routine_sleep(t_philo *philo, long ts)
{
	leave_forks(philo);
	philo->state = SLEEP;
	philo->last_sleep_date = ts;
}

void 	routine_eat(t_philo *philo, long ts)
{
	philo->state = EAT;
	philo->last_eat_date = ts;
	philo->nb_meal_max -= 1;
}

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;
	long	ts;
	char	previous_state;

	philo = (t_philo*)philo_void;
	while (philo->state != DEAD && philo->nb_meal_max != 0)
	{
		ts = get_timestamp() - philo->start_ts;
		previous_state = philo->state;
		if (philo->state != EAT
			&& (ts - philo->last_eat_date) > philo->time_to_die)
			philo->state = DEAD;
		else if (philo->state == THINK && philo->time_to_eat < ts - philo->last_eat_date)
			routine_forks(philo);
		else if (philo->state == HAS_FORKS)
			routine_eat(philo, ts);
		else if (philo->state == EAT
			&& philo->time_to_sleep < ts - philo->last_sleep_date)
			routine_sleep(philo, ts);
		else if (philo->state == SLEEP)
			philo->state = THINK;
		if (philo->state != HAS_FORKS && previous_state != philo->state)
			print_state(ts, philo->num, philo->state);
	}
	return (NULL);
}
