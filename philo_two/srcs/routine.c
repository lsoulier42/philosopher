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

void	routine_eat(t_philo *philo)
{
	if (!(philo->is_finished))
		sem_wait(philo->forks);
	if (!(philo->is_finished))
		sem_wait(philo->forks);
	philo->state = EAT;
	philo->last_eat_date = get_timestamp(philo->start_ts);
	print_state(philo, 0, NULL);
	ft_usleep(philo->time_to_eat);
	if (!(philo->is_finished))
		sem_post(philo->forks);
	if (!(philo->is_finished))
		sem_post(philo->forks);
	philo->nb_meal += 1;
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
			print_state(philo, 0, NULL);
			ft_usleep(philo->time_to_sleep);
		}
		else if (philo->state == SLEEP)
		{
			philo->state = THINK;
			print_state(philo, 0, NULL);
		}
		philo->is_finished = philo->state == DEAD
			|| (philo->nb_meal >= philo->nb_meal_max);
		usleep(10);
	}
	return (NULL);
}
