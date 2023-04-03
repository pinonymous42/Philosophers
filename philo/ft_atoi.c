/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:54:46 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/22 23:20:00 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	overflow(long i, char str, int minus)
{
	int	digit;

	digit = str - '0';
	if (minus == 1)
		if ((i >= 922337203685477580 && digit > 7)
			|| (i >= 922337203685477581))
			return (-1);
	if (minus == -1)
		if ((i >= 922337203685477580 && digit > 8)
			|| (i >= 922337203685477581))
			return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		minus;
	long	i;
	int		check;

	minus = 1;
	i = 0;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		check = overflow(i, *str, minus);
		if (check != 1)
			return (check);
		i = i * 10 + (*str - '0');
		str++;
	}
	return (i * minus);
}
