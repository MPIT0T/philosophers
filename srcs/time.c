/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:31:00 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/06 17:54:31 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philo *philo, long long time)
{
	long long	time_curr;

	time_curr = ft_get_time(philo->data);
	while (time_curr - philo->last_meal < time)
	{
		time_curr = ft_get_time(philo->data);
		pthread_mutex_lock(philo->m_last_meal);
		if (time_curr - philo->last_meal > philo->data->time_to_die)
		{
			ft_put_info(philo, DIE);
			philo->alive = false;
			philo->data->dead = true;
			pthread_mutex_unlock(philo->m_last_meal);
			return (1);
		}
		pthread_mutex_unlock(philo->m_last_meal);
	}
	return (0);
}

long long	ft_get_time(t_data *data)
{
	struct timeval	time;
	long long		time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = time.tv_usec / 1000 + time.tv_sec * 1000 - data->first_time;
	return (time_in_ms);
}
