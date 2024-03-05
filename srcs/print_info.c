/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/05 19:16:36 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_info(t_philo *philo, long long time_in_ms, char *str)
{
	pthread_mutex_lock(philo->data->print);
	printf(str, time_in_ms, philo->id, str);
	pthread_mutex_unlock(philo->data->print);
}

void	ft_put_info(t_philo *philo, enum e_action action)
{
	long long	time_in_ms;

	time_in_ms = ft_get_time(philo->data);
	if (action == FORK)
		ft_print_info(philo, time_in_ms, "%lli \033[1;36m%d \033[1;32mhas taken a fork\033[0m\n");
	else if (action == EAT)
		ft_print_info(philo, time_in_ms, "%lli \033[1;36m%d \033[1;32mis eating\033[0m\n");
	else if (action == SLEEP)
		ft_print_info(philo, time_in_ms, "%lli \033[1;36m%d \033[1;32mis sleeping\033[0m\n");
	else if (action == THINK)
		ft_print_info(philo, time_in_ms, "%lli \033[1;36m%d \033[1;32mis thinking\033[0m\n");
	else if (action == DIE)
	{
		ft_print_info(philo, time_in_ms, "%lli \033[1;36m%d \033[1;31mhas died\033[0m\n");

	}
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
	else if (error == 9)
		ft_putstr_fd("Error\n\tthread join failed\n", 2);
}

void	ft_putstr_fd(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
