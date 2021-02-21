/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:02:25 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 12:02:27 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	unlock_semaphores(t_data *philo_data)
{
	int i;

	i = -(philo_data->nb_philo);
	while (++i < philo_data->nb_philo)
		sem_post(philo_data->forks);
	usleep(10000);
}

void	unlink_semaphores(void)
{
	sem_unlink("forks");
	sem_unlink("output");
}

int		delete_semaphores(t_data *philo_data)
{
	unlock_semaphores(philo_data);
	if (sem_close(philo_data->forks) != 0)
		thread_error(SEM_CLOSE_ERROR);
	if (sem_close(philo_data->output) != 0)
		thread_error(SEM_CLOSE_ERROR);
	unlink_semaphores();
	return (0);
}

int		init_semaphores(t_data *philo_data)
{
	unlink_semaphores();
	philo_data->forks = sem_open("forks", O_RDWR | O_CREAT,
		0664, philo_data->nb_forks);
	if (philo_data->forks == SEM_FAILED)
	{
		thread_error(SEM_OPEN_ERROR);
		return (delete_semaphores(philo_data));
	}
	philo_data->output = sem_open("output", O_RDWR | O_CREAT, 0664, 1);
	if (philo_data->output == SEM_FAILED)
	{
		thread_error(SEM_OPEN_ERROR);
		return (delete_semaphores(philo_data));
	}
	return (1);
}
