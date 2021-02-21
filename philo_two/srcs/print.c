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

char	*ft_itoa(int n)
{
	char	*str;
	int		nb_char;
	int		n_copy;

	nb_char = 2;
	n_copy = n;
	while (n_copy / 10 != 0)
	{
		nb_char++;
		n_copy /= 10;
	}
	str = (char*)malloc(sizeof(char) * (nb_char + 1));
	if (!str)
		return (NULL);
	str[nb_char] = '\0';
	str[--nb_char] = ' ';
	while (--nb_char >= 0)
	{
		str[nb_char] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

void	print_state(int is_finished, char *ts_str, char *num_str, char *state)
{
	char	buffer[100];
	int		i;
	int		j;
	int		k;

	if (!is_finished)
	{
		i = -1;
		j = -1;
		k = -1;
		while (ts_str[++i])
			buffer[i] = ts_str[i];
		while (num_str[++j])
			buffer[i++] = num_str[j];
		while (state[++k])
			buffer[i++] = state[k];
		buffer[i++] = '\n';
		buffer[i] = '\0';
		write(1, buffer, i);
	}
}
