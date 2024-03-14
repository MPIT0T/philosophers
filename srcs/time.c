/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:31:00 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/09 17:09:58 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philo *philo, long long time)
{
	long long	first_time;

	first_time = ft_get_time(philo->data);
	while (ft_get_time(philo->data) - first_time < time)
	{
		if (ft_get_time(philo->data) - philo->last_meal > philo->data->time_to_die)
		{
			ft_put_info(philo, DIE);
			return (1);
		}
	}
	return (0);
}

long long	ft_get_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000 - data->first_time);
}
