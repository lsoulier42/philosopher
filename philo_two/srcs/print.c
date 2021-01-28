/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 09:38:28 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/22 09:38:40 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	print_state(long ts, int num, char state)
{
	char	*output;

	if (state == DEAD || !g_someone_has_died)
	{
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
}
