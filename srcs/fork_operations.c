/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:08:06 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/27 18:08:06 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_try_lfork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork->mutex);
	if (philo->l_fork->owner == 0)
	{
		philo->l_fork->owner = philo->id;
		ft_put_info(philo, "has taken a fork");
	}
	pthread_mutex_unlock(philo->l_fork->mutex);
	if (philo->l_fork->owner != philo->id)
		return (0);
	return (philo->id);
}

int	ft_try_rfork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork->mutex);
	if (philo->r_fork->owner == 0)
	{
		philo->r_fork->owner = philo->id;
		ft_put_info(philo, "has taken a fork");
	}
	pthread_mutex_unlock(philo->r_fork->mutex);
	if (philo->r_fork->owner != philo->id)
		return (0);
	return (philo->id);
}

