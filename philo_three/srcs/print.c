/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:09:38 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/25 11:09:47 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
