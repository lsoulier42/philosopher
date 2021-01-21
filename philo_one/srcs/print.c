/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:14:14 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/19 15:16:22 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long	get_timestamp(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000;
	ms += tv.tv_usec / 1000;
	return (ms);
}

void	print_state(long ts, int num, char state)
{
	char	*output;

	output = "";
	if (state == EAT)
		output = "is eating";
	else if (state == SLEEP)
		output = "is sleeping";
	else if (state == THINK)
		output = "is thinking";
	else if (state == DEAD)
		output = "died";
	else if (state == HAS_FORKS)
		output = "has taken a fork";
	printf("%ld %d %s\n", ts, num, output);
}
