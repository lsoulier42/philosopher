/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:01:57 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 12:01:58 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	main(int argc, char **argv)
{
	t_data	philo_data;
	int		stat_loc;
	int		nb_finished;

	nb_finished = 0;
	if (argc < MIN_NB_ARGS || argc > MAX_NB_ARGS)
		return (invalid_arg_nb());
	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	if (!init_data(&philo_data, argc, argv))
		return (EXIT_FAILURE);
	if (!load_processes(&philo_data))
		return (delete_data(&philo_data) + EXIT_FAILURE);
	while (nb_finished < philo_data.nb_philo)
	{
		waitpid(-1, &stat_loc, 0);
		if (WIFEXITED(stat_loc) && WEXITSTATUS(stat_loc) == DEAD)
			break ;
		else
			nb_finished++;
	}
	delete_data(&philo_data);
	return (EXIT_SUCCESS);
}
