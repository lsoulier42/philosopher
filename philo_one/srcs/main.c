/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:42:28 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/19 09:42:51 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
		while (philo_loop(&philo_data))
			;
		delete_data(&philo_data);
	}
	else
		return (invalid_arg_nb());
	return (EXIT_SUCCESS);
}
