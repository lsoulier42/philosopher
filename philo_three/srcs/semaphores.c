/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:38:48 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/25 11:39:00 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	init_forks(t_data *philo_data)
{
	t_fork *forks;
	int nb_wait;

	unlink_forks();
	nb_wait = philo_data->nb_forks % 2 == 0 ? philo_data->nb_forks / 2 : (philo_data->nb_forks / 2) + 1;
	forks = &(philo_data->forks);
	forks->nb_forks_available = sem_open("forks", O_RDWR | O_CREAT,
		0664, philo_data->nb_forks);
	if (forks->nb_forks_available == SEM_FAILED)
		return (0);
	forks->can_take_a_fork = sem_open("can_take", O_RDWR | O_CREAT,
		0664, nb_wait);
	if (forks->can_take_a_fork == SEM_FAILED)
	{
		sem_close(philo_data->forks.nb_forks_available);
		unlink_forks();
		return (0);
	}
	forks->someone_has_died = sem_open("dead", O_RDWR | O_CREAT, 0664, 0);
	if (forks->someone_has_died == SEM_FAILED)
	{
		sem_close(philo_data->forks.nb_forks_available);
		sem_close(philo_data->forks.can_take_a_fork);
		unlink_forks();
		return (0);
	}
	return (1);
}

int	delete_forks(t_data *philo_data)
{
	sem_close(philo_data->forks.nb_forks_available);
	sem_close(philo_data->forks.can_take_a_fork);
	sem_close(philo_data->forks.someone_has_died);
	unlink_forks();
	return (1);
}

void unlink_forks(void)
{
	sem_unlink("forks");
	sem_unlink("can_take");
	sem_unlink("dead");
}
