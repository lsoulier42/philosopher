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

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo*)philo_void;
	while (!g_someone_died)
	{
		if ((philo->last_eat_date == NOT_EATEN_YET
			|| philo->time_to_eat > get_current_timestamp() - philo->last_eat_date)
			&& (philo->state == THINK || philo->state == NONE))
		{
			take_forks(philo);
			if (philo->nb_forks_taken == 2)
			{
				philo->state = EAT;
				philo->last_eat_date = get_current_timestamp();
				print_state(philo->num, philo->state);
				leave_forks(philo);
			}
		}
		else if ((philo->last_sleep_date == NOT_SLEPT_YET
			|| philo->time_to_sleep > get_current_timestamp() - philo->last_sleep_date)
			&& (philo->state == EAT || philo->state == NONE))
		{
			philo->state = SLEEP;
			philo->last_sleep_date = get_current_timestamp();
			print_state(philo->num, philo->state);
		}
		else if ((philo->state == SLEEP || philo->state == NONE))
		{
			philo->state = THINK;
			print_state(philo->num, philo->state);
		}
		if (philo->last_eat_date != NOT_EATEN_YET
			&& get_current_timestamp() - philo->last_eat_date > philo->time_to_die)
		{
			philo->state = DEAD;
			g_someone_died = 1;
		}
	}
	return (NULL);
}
