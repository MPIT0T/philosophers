/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:49:42 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/14 19:42:35 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *nptr)
{
	size_t	i;
	long	value;
	int		sign;

	i = 0;
	value = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		value = value * 10 + nptr[i] - 48;
		i++;
	}
	return (value * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (error_msg(ARGS), 1);
	while (++i < ac)
	{
		if (!ft_isdigit(av[i]))
			return (error_msg(ARG), 1);
	}
	if (ft_atol(av[1]) < 1
		|| ft_atol(av[1]) > MAX_PHILO
		|| ft_atol(av[2]) < 60
		|| ft_atol(av[3]) < 60
		|| ft_atol(av[4]) < 60
		|| (ac == 6 && ft_atol(av[5]) < 1))
		return (error_msg(ARG), 1);
	return (0);
}
