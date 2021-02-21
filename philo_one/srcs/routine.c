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

void	*routine_death(void *philo_void)
{
	t_philo	*philo;
	int		ts;

	philo = (t_philo*)philo_void;
	while (philo->nb_meal != philo->nb_meal_max)
	{
		ts = get_timestamp(philo->start_ts);
		if ((philo->time_to_die < ts - philo->last_eat_date)
			&& philo->state != EAT)
		{
			philo->state = DEAD;
			philo->nb_meal = philo->nb_meal_max;
			philo->is_finished = 1;
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

void	routine_think(t_philo *philo)
{
	char *ts_str;
	char *num_str;

	pthread_mutex_lock(philo->output);
	philo->state = THINK;
	ts_str = ft_itoa(get_timestamp(philo->start_ts));
	num_str = ft_itoa(philo->num);
	if (ts_str && num_str)
	{
		print_state(philo->is_finished, ts_str, num_str, "is thinking");
		free(ts_str);
		free(num_str);
	}
	pthread_mutex_unlock(philo->output);
}

void	routine_sleep(t_philo *philo)
{
	char *ts_str;
	char *num_str;

	pthread_mutex_lock(philo->output);
	philo->state = SLEEP;
	ts_str = ft_itoa(get_timestamp(philo->start_ts));
	num_str = ft_itoa(philo->num);
	if (ts_str && num_str)
	{
		print_state(philo->is_finished, ts_str, num_str, "is sleeping");
		free(ts_str);
		free(num_str);
	}
	pthread_mutex_unlock(philo->output);
	ft_usleep(philo->time_to_sleep);
}

void	routine_eat(t_philo *philo)
{
	char *ts_str;
	char *num_str;

	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->second_fork);
	philo->state = EAT;
	philo->nb_meal += 1;
	philo->last_eat_date = get_timestamp(philo->start_ts);
	pthread_mutex_lock(philo->output);
	ts_str = ft_itoa(philo->last_eat_date);
	num_str = ft_itoa(philo->num);
	if (ts_str && num_str)
	{
		print_state(philo->is_finished, ts_str, num_str, "has taken a fork");
		print_state(philo->is_finished, ts_str, num_str, "has taken a fork");
		print_state(philo->is_finished, ts_str, num_str, "is eating");
		free(ts_str);
		free(num_str);
	}
	pthread_mutex_unlock(philo->output);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	*philo_routine(void *philo_void)
{
	t_philo		*philo;
	pthread_t	death;

	philo = (t_philo*)philo_void;
	philo->start_ts = get_timestamp(0);
	philo->last_eat_date = 0;
	if (pthread_create(&death, NULL, &routine_death, philo) != 0)
		return (thread_error(CREATE_THREAD_ERROR));
	pthread_detach(death);
	while (philo->nb_meal < philo->nb_meal_max)
	{
		routine_eat(philo);
		routine_sleep(philo);
		routine_think(philo);
		usleep(100);
	}
	philo->is_finished = 1;
	return (NULL);
}
