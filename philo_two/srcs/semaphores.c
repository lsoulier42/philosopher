/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 09:47:51 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/22 09:48:01 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	init_forks(t_data *philo_data)
{
	t_fork *forks;

	unlink_forks();
	forks = &(philo_data->forks);
	forks->nb_forks_available = sem_open("forks", O_RDWR | O_CREAT,
		0664, philo_data->nb_forks);
	if (forks->nb_forks_available == SEM_FAILED)
		return (0);
	forks->can_take_a_fork = sem_open("can_take", O_RDWR | O_CREAT,
		0664, philo_data->nb_forks - 1);
	if (forks->can_take_a_fork == SEM_FAILED)
	{
		sem_close(philo_data->forks.nb_forks_available);
		unlink_forks();
		return (0);
	}
	return (1);
}

int	delete_forks(t_data *philo_data)
{
	sem_close(philo_data->forks.nb_forks_available);
	sem_close(philo_data->forks.can_take_a_fork);
	unlink_forks();
	return (1);
}

void unlink_forks(void)
{
	sem_unlink("forks");
	sem_unlink("can_take");
}
