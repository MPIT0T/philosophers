/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:31:00 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/04 18:59:42 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philo *philo, long long time)
{
	long long	count;

	count = 0;
	while (count < time)
	{
		if (ft_get_time(philo->data) - philo->last_meal > philo->data->time_to_die)
		{
			ft_put_info(philo, "has died");
			philo->alive = false;
			philo->data->dead = true;
			return (1);
		}
		usleep(1000);
		count++;
	}
	return (0);
}

long long ft_get_time(t_data *data)
{
	struct timeval	time;
	long long		time_in_ms;

//	pthread_mutex_lock(data->time);
	gettimeofday(&time, NULL);
	time_in_ms = time.tv_usec / 1000 + time.tv_sec * 1000 - data->first_time;
//	pthread_mutex_unlock(data->time);
	return (time_in_ms);
}
