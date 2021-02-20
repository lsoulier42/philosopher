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

int	alloc_struct(t_data *philo_data)
{
	int nb_philo;
	int nb_forks;

	nb_philo = philo_data->nb_philo;
	nb_forks = philo_data->nb_forks;
	philo_data->forks = malloc(sizeof(pthread_mutex_t) * nb_forks);
	if (!philo_data->forks)
		return (free_struct(philo_data));
	philo_data->philosophers_threads = malloc(sizeof(pthread_t) * nb_philo);
	if (!philo_data->philosophers_threads)
		return (free_struct(philo_data));
	philo_data->philosophers = malloc(sizeof(t_philo) * nb_philo);
	if (!philo_data->philosophers)
		return (free_struct(philo_data));
	return (1);
}

int	init_struct(t_data *philo_data)
{
	if (!init_mutexes(philo_data))
		return (free_struct(philo_data));
	if (!init_philosophers(philo_data))
		return (delete_data(philo_data));
	return (1);
}

int	free_struct(t_data *philo_data)
{
	if (philo_data->forks)
		free(philo_data->forks);
	if (philo_data->philosophers_threads)
		free(philo_data->philosophers_threads);
	if (philo_data->philosophers)
		free(philo_data->philosophers);
	return (0);
}

int	init_data(t_data *philo_data, int argc, char **argv)
{
	philo_data->nb_philo = ft_atoi(argv[1]);
	philo_data->nb_forks = philo_data->nb_philo == 1 ? 2 : philo_data->nb_philo;
	printf("%d philosophers are wakening\n", philo_data->nb_philo);
	philo_data->time_to_die = ft_atoi(argv[2]);
	philo_data->time_to_eat = ft_atoi(argv[3]);
	philo_data->time_to_sleep = ft_atoi(argv[4]);
	philo_data->nb_meal_max = UNLIMITED_MEAL;
	if (argc == 6)
		philo_data->nb_meal_max = ft_atoi(argv[5]);
	philo_data->nb_finished = 0;
	philo_data->forks = NULL;
	philo_data->philosophers_threads = NULL;
	philo_data->philosophers = NULL;
	if (!alloc_struct(philo_data))
		return (0);
	if (!init_struct(philo_data))
		return (0);
	return (1);
}

int	delete_data(t_data *philo_data)
{
	delete_mutexes(philo_data);
	delete_threads(philo_data);
	free_struct(philo_data);
	return (0);
}
