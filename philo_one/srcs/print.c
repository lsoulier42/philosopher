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

void	print_state(int ts, int num, char state)
{
	char	*output;

	if (state == DEAD || !g_someone_has_died)
	{
		if (state == EAT)
			output = "is eating";
		else if (state == SLEEP)
			output = "is sleeping";
		else if (state == THINK)
			output = "is thinking";
		else if (state == DEAD)
			output = "died";
		else
			output = "has taken a fork";
		printf("%d %d %s\n", ts, num, output);
	}
}
