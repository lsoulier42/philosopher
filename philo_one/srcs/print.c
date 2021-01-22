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

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

void	print_state(int ts, int num, char state)
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
	printf("%d %d %s\n", ts, num, output);
}
