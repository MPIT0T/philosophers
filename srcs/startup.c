/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:27:45 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/14 18:06:30 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_death(t_data *data)
{
	size_t	i;

	while (ft_dead(data))
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (ft_get_time(data->philo[i].data) - data->philo[i].last_meal
				> data->philo[i].data->time_to_die)
				ft_make_dead(data);
		}
	}
}

int	ft_create_threads(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&data->philo[i].thread, NULL,
					&ft_routine_pair, &data->philo[i]))
				return (error_msg(THREAD), 1);
		}
		else
		{
			if (pthread_create(&data->philo[i].thread, NULL,
					&ft_routine_odd, &data->philo[i]))
				return (error_msg(THREAD), 1);
		}
	}
	return (0);
}

int	ft_startup(t_data *data)
{
	size_t	i;

	i = -1;
	pthread_mutex_lock(&data->m_tab[READY]);
	if (ft_create_threads(data))
	{
		ft_make_dead(data);
		pthread_mutex_unlock(&data->m_tab[READY]);
		return (1);
	}
	data->first_time = ft_get_time(data);
	pthread_mutex_unlock(&data->m_tab[READY]);
	ft_check_death(data);
	while (++i < data->nb_philo)
		pthread_join(data->philo[i].thread, NULL);
	return (0);
}

int	ft_check_meals(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (data->philo[i].meals != data->max_meals)
			break ;
	}
	if (i == data->nb_philo)
		return (1);
	return (0);
}
