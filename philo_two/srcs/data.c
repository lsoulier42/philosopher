/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 09:29:59 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/25 11:25:29 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	alloc_struct(t_data *philo_data)
{
	philo_data->threads = (pthread_t*)malloc(sizeof(pthread_t)
		* philo_data->nb_philo);
	if (!(philo_data->threads))
		return (free_struct(philo_data));
	philo_data->philosophers = (t_philo*)malloc(sizeof(t_philo)
		* philo_data->nb_philo);
	if (!(philo_data->philosophers))
		return (free_struct(philo_data));
	return (1);
}

int	init_struct(t_data *philo_data)
{
	if (!init_forks(philo_data))
		return (free_struct(philo_data));
	init_philosophers(philo_data);
	return (1);
}

int	free_struct(t_data *philo_data)
{
	if (philo_data->threads)
		free(philo_data->threads);
	if (philo_data->philosophers)
		free(philo_data->philosophers);
	return (0);
}

int	init_data(t_data *philo_data, int argc, char **argv)
{
	philo_data->nb_philo = ft_atoi(argv[1]);
	philo_data->nb_forks = philo_data->nb_philo == 1 ? 2 : philo_data->nb_philo;
	printf("%d philosophes ont ete crees\n", philo_data->nb_philo);
	philo_data->time_to_die = ft_atoi(argv[2]);
	philo_data->time_to_eat = ft_atoi(argv[3]);
	philo_data->time_to_sleep = ft_atoi(argv[4]);
	philo_data->start_ts = get_timestamp();
	philo_data->someone_has_died = 0;
	philo_data->nb_meal_max = UNLIMITED_MEAL;
	if (argc == 6)
		philo_data->nb_meal_max = ft_atoi(argv[5]);
	philo_data->threads = NULL;
	philo_data->philosophers = NULL;
	if (!alloc_struct(philo_data))
		return (0);
	if (!init_struct(philo_data))
		return (0);
	return (1);
}

int	delete_data(t_data *philo_data)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < philo_data->nb_forks)
		sem_post(philo_data->forks.nb_forks_available);
	while (++j < philo_data->nb_forks)
		sem_post(philo_data->forks.can_take_a_fork);
	if (philo_data->philosophers)
		delete_philosophers(philo_data);
	delete_forks(philo_data);
	return (free_struct(philo_data));
}
