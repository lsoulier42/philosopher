/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:27:53 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/19 10:28:01 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	philo_loop(t_data *philo_data)
{
	int i;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		if (!(philo_data->philosophers[i].alive))
		{
			philo_data->someone_died = 1;
			print_state(philo_data->philosophers[i].num, DIED);
			break ;
		}
	}
	return (1);
}
