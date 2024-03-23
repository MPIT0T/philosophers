/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_pair.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:33:33 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/23 20:30:33 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat(t_philo *philo)
{
	while (!ft_try_rfork(philo))
	{
		if (ft_get_time(philo->data) - philo->last_meal > philo->data->time_to_die)
			return (ft_put_info(philo, DIE));
	}
//	ft_put_info(philo, FORK);
	while (!ft_try_lfork(philo))
	{
		if (ft_get_time(philo->data) - philo->last_meal > philo->data->time_to_die)
			return (ft_put_info(philo, DIE));
	}
//	ft_put_info(philo, FORK);
//	philo->last_meal = ft_get_time(philo->data);
	ft_put_info(philo, EAT);
	ft_usleep(philo, philo->data->time_to_eat);
	philo->last_meal = ft_get_time(philo->data);
	philo->meals++;
	ft_release_rfork(philo);
	ft_release_lfork(philo);
}

static void	ft_one_philo(t_philo *philo)
{
	ft_put_info(philo, FORK);
	ft_usleep(philo, philo->data->time_to_die);
	ft_put_info(philo, DIE);
	usleep(500);
}

void	*ft_routine_pair(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
//	while (!philo->data->ready)
//		continue ;
	pthread_mutex_lock(&philo->data->m_tab[READY]);
	pthread_mutex_unlock(&philo->data->m_tab[READY]);
	if (philo->data->nb_philo == 1)
		return (ft_one_philo(philo), NULL);
	while (!ft_dead(philo->data)
		&& (philo->data->max_meals == 0
			|| philo->meals < philo->data->max_meals))
	{
		ft_eat(philo);
		if (ft_dead(philo->data)
			|| (philo->data->max_meals != 0
				&& philo->meals >= philo->data->max_meals))
			break ;
		if (ft_sleep(philo))
			break ;
		if (ft_dead(philo->data))
			break ;
		ft_put_info(philo, THINK);
//		usleep(500);
	}
	usleep(500);
	return (NULL);
}
