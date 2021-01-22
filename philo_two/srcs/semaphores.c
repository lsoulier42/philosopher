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

	forks = &(philo_data->forks);
	forks->nb_forks_available = sem_open("forks", O_RDWR | O_CREAT,
		0664, philo_data->nb_forks);
	if (forks->nb_forks_available == SEM_FAILED)
		return (0);
	forks->current_nb = philo_data->nb_forks;
	return (1);
}

int delete_forks(t_data *philo_data)
{
	sem_unlink("forks");
	sem_close(philo_data->forks.nb_forks_available);
	return (1);
}
