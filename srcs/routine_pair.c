/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_pair.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:33:33 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/04 19:04:13 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat_pair(t_philo *philo)
{
	while (!ft_try_rfork(philo))
	{
		pthread_mutex_lock(philo->m_last_meal);
		if (ft_get_time(philo->data) - philo->last_meal > philo->data->time_to_die)
			return (ft_put_info(philo, "has died"), 1);
		pthread_mutex_unlock(philo->m_last_meal);
	}
	while (!ft_try_lfork(philo))
	{
		pthread_mutex_lock(philo->m_last_meal);
		if (ft_get_time(philo->data) - philo->last_meal > philo->data->time_to_die)
			return (ft_put_info(philo, "has died"), 1);
		pthread_mutex_unlock(philo->m_last_meal);
	}
	ft_put_info(philo, "is eating");
	ft_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_lock(philo->m_last_meal);
	philo->last_meal = ft_get_time(philo->data);
	pthread_mutex_unlock(philo->m_last_meal);
	ft_release_rfork(philo);
	ft_release_lfork(philo);
	return (0);
}

void	*ft_routine_pair(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->data->ready);
	pthread_mutex_unlock(philo->data->ready);
	while (philo->alive && ft_dead(philo->data))
	{
		if (ft_eat_pair(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		ft_put_info(philo, "is thinking");
	}
	pthread_mutex_lock(philo->data->m_dead);
	philo->data->dead = true;
	pthread_mutex_unlock(philo->data->m_dead);
	return (NULL);
}
