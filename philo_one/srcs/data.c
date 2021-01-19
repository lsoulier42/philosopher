/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:43:07 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/19 09:43:18 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	init_data(t_data *philo_data, int argc, char **argv)
{
	philo_data->nb_philo = ft_atoi(argv[1]);
	philo_data->time_to_die = ft_atoi(argv[2]);
	philo_data->time_to_eat = ft_atoi(argv[3]);
	philo_data->time_to_sleep = ft_atoi(argv[4]);
	philo_data->nb_meal = 0;
	philo_data->nb_meal_max = UNLIMITED_MEAL;
	if (argc == 6)
		philo_data->nb_meal_max = ft_atoi(argv[5]);
	philo_data->nb_forks = philo_data->nb_philo;
	philo_data->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)
		* (philo_data->nb_forks));
	if (!philo_data->forks)
		return (0);
	philo_data->someone_died = 0;
	philo_data->philosophers = (t_philo*)malloc(sizeof(t_philo)
		* philo_data->nb_philo);
	if (!(philo_data->philosophers))
	{
		free(philo_data->forks);
		return (0);
	}
	if (!init_threads(philo_data, philo_data->philosophers))
	{
		free(philo_data->forks);
		free(philo_data->philosophers);
		return (0);
	}
	return (1);
}

int	check_arg(int argc, char **argv)
{
	int i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_isnum(argv[i]))
			return (invalid_arg_num(argv[i]));
		if (argv[i][0] == '-')
			return (invalid_arg_neg(argv[i]));
	}
	return (1);
}


