/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:29:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/14 19:09:09 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_put_eated(t_data *data)
{
	pthread_mutex_lock(&data->m_tab[PRINT]);
	printf("\033[1;32mAll philosophers have eaten %ld times\033[0m\n",
		data->max_meals);
	pthread_mutex_unlock(&data->m_tab[PRINT]);
}

void	ft_print_info(t_philo *philo, long long time_in_ms, char *str)
{
	pthread_mutex_lock(&philo->data->m_tab[PRINT]);
	if (!ft_dead(philo->data))
		printf(str, time_in_ms, philo->id, str);
	pthread_mutex_unlock(&philo->data->m_tab[PRINT]);
}

void	ft_put_info(t_philo *philo, t_action action)
{
	long long	time_in_ms;

	time_in_ms = ft_get_time(philo->data);
	if (action == FORK)
		ft_print_info(philo, time_in_ms,
			"%lli %d has taken a fork\n");
	else if (action == EAT)
		ft_print_info(philo, time_in_ms,
			"%lli %d is eating\n");
	else if (action == SLEEP)
		ft_print_info(philo, time_in_ms,
			"%lli %d is sleeping\n");
	else if (action == THINK)
		ft_print_info(philo, time_in_ms,
			"%lli %d is thinking\n");
	else if (action == DIE)
	{
		ft_print_info(philo, time_in_ms,
			"%lli %d has died\n");
		ft_make_dead(philo->data);
	}
}

void	error_msg(t_error error)
{
	if (error == ARGS)
		ft_putstr_fd("\033[1;31mError\033[0m:\n\tWrong number of arguments.\n",
			2);
	else if (error == ARG)
		ft_putstr_fd("\033[1;31mError\033[0m:\n\tWrong argument.\n", 2);
	else if (error == MALLOC)
		ft_putstr_fd("\033[1;31mError\033[0m:\n\tMalloc failed.\n", 2);
	else if (error == MUTEX)
		ft_putstr_fd("\033[1;31mError\033[0m:\n\tMutex error.\n", 2);
	else if (error == THREAD)
		ft_putstr_fd("\033[1;31mError\033[0m:\n\tThreading error.\n", 2);
}

void	ft_putstr_fd(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
