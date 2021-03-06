/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:07:24 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 00:07:25 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	monitor_loop(t_data *philo_data)
{
	int i;
	int nb_finished;

	nb_finished = 0;
	i = -1;
	while (++i < philo_data->nb_philo)
	{
		if (philo_data->philosophers[i].state == DEAD)
		{
			nb_finished = philo_data->nb_philo;
			sem_wait(philo_data->philosophers[i].output);
			printf("%ld %d died\n",
				get_timestamp(philo_data->philosophers[i].start_ts), i + 1);
			i = -1;
			while (++i < philo_data->nb_philo)
				*(&philo_data->philosophers[i].is_finished) = 1;
			break ;
		}
		nb_finished += philo_data->philosophers[i].is_finished;
	}
	return (nb_finished == philo_data->nb_philo);
}

int	main(int argc, char **argv)
{
	t_data	philo_data;

	if (argc >= MIN_NB_ARGS && argc <= MAX_NB_ARGS)
	{
		if (!check_args(argc, argv))
			return (EXIT_FAILURE);
		if (!init_data(&philo_data, argc, argv))
			return (EXIT_FAILURE);
		if (!load_threads(&philo_data))
			return (delete_data(&philo_data) + EXIT_FAILURE);
		while (!monitor_loop(&philo_data))
			usleep(100);
		delete_data(&philo_data);
	}
	else
		return (invalid_arg_nb());
	return (EXIT_SUCCESS);
}
