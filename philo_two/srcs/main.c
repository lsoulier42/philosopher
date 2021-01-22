/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 09:18:36 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/22 09:18:46 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
		while (1)
		{
			if (!philo_loop(&philo_data))
				break ;
		}
		delete_data(&philo_data);
	}
	else
		return (invalid_arg_nb());
	return (EXIT_SUCCESS);
}
