/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 09:33:51 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/22 09:34:02 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long	get_timestamp(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000;
	ms += tv.tv_usec / 1000;
	return (ms);
}

int		ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int		ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
			|| c == '\r' || c == '\t' || c == '\v');
}

int		ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	r_val;

	i = 0;
	sign = 1;
	r_val = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r_val = r_val * 10 + str[i] - '0';
		i++;
	}
	return (r_val * sign);
}
