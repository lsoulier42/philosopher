/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:07:14 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 00:07:15 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	alloc_struct(t_data *philo_data)
{
	int nb_philo;

	nb_philo = philo_data->nb_philo;
	philo_data->philosophers = malloc(sizeof(t_philo) * nb_philo);
	if (!philo_data->philosophers)
		return (0);
	return (1);
}

int	init_struct(t_data *philo_data)
{
	if (!init_semaphores(philo_data))
		return (delete_data(philo_data));
	if (!init_philosophers(philo_data))
		return (delete_data(philo_data));
	return (1);
}

int	init_data(t_data *philo_data, int argc, char **argv)
{
	philo_data->nb_philo = ft_atoi(argv[1]);
	philo_data->nb_forks = philo_data->nb_philo == 1 ? 2 : philo_data->nb_philo;
	philo_data->time_to_die = ft_atoi(argv[2]);
	philo_data->time_to_eat = ft_atoi(argv[3]);
	philo_data->time_to_sleep = ft_atoi(argv[4]);
	philo_data->nb_meal_max = INT_MAX;
	if (argc == 6)
		philo_data->nb_meal_max = ft_atoi(argv[5]);
	philo_data->nb_finished = 0;
	philo_data->philosophers = NULL;
	if (!alloc_struct(philo_data))
		return (0);
	if (!init_struct(philo_data))
		return (0);
	return (1);
}

int	delete_data(t_data *philo_data)
{
	delete_semaphores(philo_data);
	if (philo_data->philosophers)
		free(philo_data->philosophers);
	return (0);
}
