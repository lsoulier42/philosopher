/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:38:41 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/21 17:38:42 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long	get_timestamp(long start_ts)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + tv.tv_usec / 1000) - start_ts);
}

void	ft_usleep(int duration)
{
	long start;
	long current;

	start = get_timestamp(0);
	current = start;
	while (duration > current - start)
	{
		usleep(100);
		current = get_timestamp(0);
	}
}
