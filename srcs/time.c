/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:31:00 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/01 16:09:14 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_philo *philo, long long time)
{
	long long	count;

	count = 0;
	while (count < time * 1000)
	{
		if (ft_get_time(philo->data) - philo->last_meal > philo->data->time_to_die)
		{
			ft_put_info(philo, "has died");
			philo->alive = false;
			philo->data->dead = true;
			return ;
		}
		usleep(1);
		time++;
	}
}

long long ft_get_time(t_data *data)
{
	struct timeval time;

	pthread_mutex_lock(data->time);
	gettimeofday(&time, NULL);
	pthread_mutex_unlock(data->time);
	return (time.tv_usec / 1000 + time.tv_sec * 1000 - data->first_time);
}
