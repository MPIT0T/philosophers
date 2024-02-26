/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:49:42 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/26 19:54:21 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_msg(int error)
{
	if (error == 1)
		ft_putstr_fd("Error:\n\twrong number of arguments\n", 2);
	else if (error == 2)
		ft_putstr_fd("Error:\n\twrong argument\n", 2);
	else if (error == 3)
		ft_putstr_fd("Error:\n\tmalloc failed\n", 2);
	else if (error == 4)
		ft_putstr_fd("Error:\n\tmutex init failed\n", 2);
	else if (error == 5)
		ft_putstr_fd("Error:\n\tthread creation failed\n", 2);
	else if (error == 6)
		ft_putstr_fd("Error:\n\tmutex lock failed\n", 2);
	else if (error == 7)
		ft_putstr_fd("Error:\n\tmutex unlock failed\n", 2);
	else if (error == 8)
		ft_putstr_fd("Error:\n\tmutex destroy failed\n", 2);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		value;
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

void	ft_putstr_fd(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

long long ft_get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}
