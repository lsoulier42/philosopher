/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:07:18 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 00:07:19 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		check_args(int argc, char **argv)
{
	int i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_isnum(argv[i]))
			return (invalid_arg_num(argv[i]));
		if (argv[i][0] == '-' || argv[i][0] == '0')
			return (invalid_arg_neg(argv[i]));
	}
	return (1);
}

int		invalid_arg_num(char *arg)
{
	printf("Error.\nThis argument is not numeric: `%s'\n", arg);
	return (0);
}

int		invalid_arg_neg(char *arg)
{
	printf("Error.\nThis argument is negative: `%s'\n", arg);
	return (0);
}

int		invalid_arg_nb(void)
{
	printf("Error.\nInvalid number of arguments :\n");
	printf("1. number_of_philosopher\n");
	printf("2. time_to_die (ms)\n");
	printf("3. time_to_eat (ms)\n");
	printf("4. time_to_sleep (ms)\n");
	printf("5. (optional) number_of_time_each_philosophers_must_eat\n");
	return (EXIT_FAILURE);
}

void	*thread_error(int code)
{
	char **errors;

	errors = (char *[TOTAL_THREAD_ERRORS]){"Creating thread went wrong",
		"Opening semaphore went wrong", "Closing semaphore went wrong",
		"Posting semaphore went wrong", "Waiting semaphore went wrong",
		"Detaching thread went wrong"};
	printf("Error\n%s\n", errors[code]);
	return (NULL);
}
