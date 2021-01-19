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

long long	get_current_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec);
}

void		print_state(int num, char state)
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
	else if (state == HAS_TAKEN_FORK)
		output = "has taken a fork";
	printf("%lld %d %s\n",
		get_current_timestamp(),
		num,
		output);
}
