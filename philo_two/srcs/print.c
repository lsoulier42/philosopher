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

void	finish_philosophers(t_data *philo_data)
{
	int		i;
	t_philo	*current;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		current = philo_data->philosophers + i;
		current->is_finished = 1;
	}
}

void	print_state(t_philo *philo, int is_dead, t_data *philo_data)
{
	char	**outputs;
	int		ts;

	outputs = (char *[TOTAL_STATES]){"is eating", "is sleeping",
		"is thinking", "has taken a fork", "died"};
	if (sem_wait(philo->output) == 0 && !(philo->is_finished))
	{
		ts = get_timestamp(philo->start_ts);
		if (philo->state != EAT)
			printf("%d %d %s\n", ts, philo->num, outputs[philo->state]);
		else
			printf("%d %d %s\n%d %d %s\n%d %d %s\n", ts,
				philo->num, outputs[HAS_FORKS], ts,
				philo->num, outputs[HAS_FORKS], ts,
				philo->num, outputs[EAT]);
		if (!is_dead && !(philo->is_finished))
			sem_post(philo->output);
		else if (philo_data)
			finish_philosophers(philo_data);
	}
}
