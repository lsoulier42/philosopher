/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:12:15 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/25 11:12:24 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	philo_loop(t_data *philo_data)
{
	int i;

	i = -1;
	sem_wait(philo_data->forks.someone_has_died);
	while(++i < philo_data->nb_philo)
		kill(philo_data->process_id[i], SIGKILL);
	return (0);
}
