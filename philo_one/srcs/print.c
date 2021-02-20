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
	int		ts;

	outputs = (char *[TOTAL_STATES]){"is eating", "is sleeping",
		"is thinking", "has taken a fork", "died"};
	if (pthread_mutex_lock(philo->output) == 0)
	{
		ts = get_timestamp(philo->start_ts);
		if (philo->state != EAT)
			printf("%d %d %s\n", ts, philo->num, outputs[philo->state]);
		else
			printf("%d %d %s\n%d %d %s\n%d %d %s\n", ts,
				philo->num, outputs[HAS_FORKS], ts,
				philo->num, outputs[HAS_FORKS], ts, philo->num, outputs[EAT]);
		if (!is_dead)
			pthread_mutex_unlock(philo->output);
	}
}
