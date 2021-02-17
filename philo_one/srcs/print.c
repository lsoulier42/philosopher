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

void	print_state(t_philo *philo, int is_dead)
{
	char	**outputs;

	outputs = (char *[TOTAL_STATES]){"is eating", "is sleeping",
		"is thinking", "has taken a fork", "died"};
	if (pthread_mutex_lock(philo->output) != 0)
		thread_error(MUTEX_LOCK_ERROR);
	else
	{
		printf("%ld %d %s\n", get_timestamp(philo->start_ts),
			philo->num, outputs[philo->state]);
		if (!is_dead)
			if (pthread_mutex_unlock(philo->output) != 0)
				thread_error(MUTEX_UNLOCK_ERROR);
	}
}
