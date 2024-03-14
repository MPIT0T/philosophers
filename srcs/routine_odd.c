/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_odd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:33:30 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/14 18:08:44 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat_odd(t_philo *philo)
{
	while (!ft_try_lfork(philo))
	{
		if (ft_get_time(philo->data) - philo->last_meal
			> philo->data->time_to_die)
			return (ft_put_info(philo, DIE), 1);
	}
	while (!ft_try_rfork(philo))
	{
		if (ft_get_time(philo->data) - philo->last_meal
			> philo->data->time_to_die)
			return (ft_put_info(philo, DIE), 1);
	}
	philo->last_meal = ft_get_time(philo->data);
	ft_put_info(philo, EAT);
	ft_usleep(philo, philo->data->time_to_eat);
	philo->last_meal = ft_get_time(philo->data);
	philo->meals++;
	ft_release_lfork(philo);
	ft_release_rfork(philo);
	return (0);
}

void	*ft_routine_odd(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->m_tab[READY]);
	pthread_mutex_unlock(&philo->data->m_tab[READY]);
	while (!ft_dead(philo->data)
		&& (philo->data->max_meals == 0
			|| philo->meals < philo->data->max_meals))
	{
		if (ft_eat_odd(philo))
			break ;
		if (ft_dead(philo->data)
			|| (philo->data->max_meals != 0
				&& philo->meals >= philo->data->max_meals))
			break ;
		if (ft_sleep(philo))
			break ;
		if (ft_dead(philo->data))
			break ;
		ft_put_info(philo, THINK);
	}
	return (NULL);
}
