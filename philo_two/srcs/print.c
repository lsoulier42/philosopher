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
	long	ts;

	outputs = (char *[TOTAL_STATES]){"is eating", "is sleeping",
		"is thinking", "has taken a fork", "died"};
	if (sem_wait(philo->output) == 0
		&& *(philo->nb_finished) != philo->nb_philo)
	{
		ts = get_timestamp(philo->start_ts);
		if (philo->state != EAT)
			printf("%ld %d %s\n", ts, philo->num, outputs[philo->state]);
		else
			printf("%ld %d %s\n%ld %d %s\n%ld %d %s\n", ts,
			philo->num, outputs[HAS_FORKS], ts,
			philo->num, outputs[HAS_FORKS], ts,
			philo->num, outputs[EAT]);
		if (!is_dead && *(philo->nb_finished) != philo->nb_philo)
			sem_post(philo->output);
	}
}
