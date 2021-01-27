/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:12:15 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/25 11:12:24 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void *monitoring_routine(void *data_void)
{
	t_process	*current;
	int			stat_loc;
	int 		everyone_has_eaten;

	current = (t_process*)data_void;
	everyone_has_eaten = 0;
	waitpid(current->process_id, &stat_loc, WNOHANG);
	if (WIFEXITED(stat_loc))
	{
		if (WEXITSTATUS(stat_loc) == DEAD)
			*(current->someone_has_died) = 1;
		else
			everyone_has_eaten = 1;
	}
	while(!(*(current->someone_has_died)) && !everyone_has_eaten)
		;
	kill(current->process_id, SIGTERM);
	return (NULL);
}

int	philo_loop(t_data *philo_data)
{
	int			i;
	pthread_t	*monitoring;
	int 		is_finish;

	i = -1;
	is_finish = 0;
	monitoring = (pthread_t*)malloc(sizeof(pthread_t) * (philo_data->nb_philo));
	if (!monitoring)
		return (0);
	while (++i < philo_data->nb_philo)
	{
		if (pthread_create(&(monitoring[i]), NULL, &monitoring_routine, philo_data->process + i) != 0)
			return (0);
	}
	while (!is_finish)
	{
		while (++i < philo_data->nb_philo)
		{
			is_finish = 1;
			if (pthread_detach(monitoring[i]) != 0)
				is_finish = 0;
		}
	}
	free(monitoring);
	return (0);
}
