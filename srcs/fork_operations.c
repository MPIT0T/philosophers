/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:08:06 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/04 13:18:58 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_try_lfork(t_philo *philo)
{
	if (philo->l_fork->owner == 0)
	{
		pthread_mutex_lock(philo->l_fork->mutex);
		philo->l_fork->owner = philo->id;
		ft_put_info(philo, FORK);
		pthread_mutex_unlock(philo->l_fork->mutex);
	}
	else
		return (0);
	return (philo->id);
}

int	ft_try_rfork(t_philo *philo)
{
	if (philo->r_fork->owner == 0)
	{
		pthread_mutex_lock(philo->r_fork->mutex);
		philo->r_fork->owner = philo->id;
		ft_put_info(philo, FORK);
		pthread_mutex_unlock(philo->r_fork->mutex);
	}
	else
		return (0);
	return (philo->id);
}

int	ft_release_lfork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork->mutex);
	philo->l_fork->owner = 0;
	pthread_mutex_unlock(philo->l_fork->mutex);
	return (0);
}

int	ft_release_rfork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork->mutex);
	philo->r_fork->owner = 0;
	pthread_mutex_unlock(philo->r_fork->mutex);
	return (0);
}
