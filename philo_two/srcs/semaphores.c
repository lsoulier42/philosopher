/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:08:26 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 00:08:29 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void unlink_semaphores(void)
{
	sem_unlink("forks");
	sem_unlink("output");
	sem_unlink("is dead");
}

int delete_semaphores(t_data *philo_data)
{
	if(sem_close(philo_data->forks) != 0)
		thread_error(SEM_CLOSE_ERROR);
	if(sem_close(philo_data->output) != 0)
		thread_error(SEM_CLOSE_ERROR);
	if(sem_close(philo_data->is_dead) != 0)
		thread_error(SEM_CLOSE_ERROR);
	unlink_semaphores();
	return (0);
}

int init_semaphores(t_data *philo_data)
{
	unlink_semaphores();
	philo_data->forks = sem_open("forks", O_RDWR | O_CREAT, 0664, philo_data->nb_forks);
	if (philo_data->forks == SEM_FAILED)
	{
		thread_error(SEM_OPEN_ERROR);
		return(delete_semaphores(philo_data));
	}
	philo_data->output = sem_open("output", O_RDWR | O_CREAT, 0664, 1);
	if (philo_data->output == SEM_FAILED)
	{
		thread_error(SEM_OPEN_ERROR);
		return(delete_semaphores(philo_data));
	}
	philo_data->is_dead = sem_open("is dead", O_RDWR | O_CREAT, 0664, 1);
	if (philo_data->is_dead == SEM_FAILED)
	{
		thread_error(SEM_OPEN_ERROR);
		return(delete_semaphores(philo_data));
	}
	if(sem_wait(philo_data->is_dead) != 0)
		thread_error(SEM_WAIT_ERROR);
	return (1);
}
