/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:31:00 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/27 17:16:56 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_philo *philo, long long time)
{
	long long	count;

	count = 0;
	while (count < time)
	{
		if (philo->last_meal != 0 && ft_get_time() - philo->last_meal > philo->data->time_to_die)
		{
			ft_put_info(philo, "has died");
			philo->alive = false;
			philo->data->dead = true;
			return ;
		}
		usleep(1000);
		time++;
	}
}

long long ft_get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}
