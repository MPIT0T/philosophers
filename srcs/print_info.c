/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/27 17:16:56 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_put_info(t_philo *philo, const char *str)
{
	long long	time_in_ms;

	time_in_ms = ft_get_time() - philo->data->first_time;
	pthread_mutex_lock(philo->data->print);
	printf("%lli %d %s\n", time_in_ms, philo->id, str);
	pthread_mutex_unlock(philo->data->print);
}

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

void	ft_putstr_fd(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
