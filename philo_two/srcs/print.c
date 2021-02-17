/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:07:31 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 00:07:33 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	print_state(t_philo *philo, int is_dead)
{
	char	**outputs;

	outputs = (char *[TOTAL_STATES]){"is eating", "is sleeping",
		"is thinking", "has taken a fork", "died"};
	if (sem_wait(philo->output) != 0)
		thread_error(SEM_WAIT_ERROR);
	else
	{
		printf("%ld %d %s\n", get_timestamp(philo->start_ts),
			philo->num, outputs[philo->state]);
		if (!is_dead)
			if (sem_post(philo->output) != 0)
				thread_error(SEM_POST_ERROR);
	}
}
