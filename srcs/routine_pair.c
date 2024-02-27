/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_pair.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:33:33 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/27 17:16:56 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_eat_pair(t_philo *philo)
{
	while (!ft_try_rfork(philo))
	{
		if (ft_get_time() - philo->last_meal > philo->data->time_to_die)
			return (ft_put_info(philo, "has died"), 1);
	}
	while (!ft_try_lfork(philo))
	{
		if (ft_get_time() - philo->last_meal > philo->data->time_to_die)
			return (ft_put_info(philo, "has died"), 1);
	}
	ft_put_info(philo, "is eating");
	ft_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_lock(philo->r_fork->mutex);
	philo->r_fork->owner = 0;
	pthread_mutex_unlock(philo->r_fork->mutex);
	pthread_mutex_lock(philo->l_fork->mutex);
	philo->l_fork->owner = 0;
	pthread_mutex_unlock(philo->l_fork->mutex);
	return (0);
}

void	*ft_routine_pair(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->ready = true;
	while (!everyone_ready(philo->data));
	while (philo->alive)
	{
		ft_eat_pair(philo);
		ft_sleep(philo);
		ft_put_info(philo, "is thinking");
	}
	return (NULL);
}
