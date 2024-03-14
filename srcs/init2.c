/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:44:34 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/14 18:16:41 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_forks(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
		{
			while (i--)
				pthread_mutex_destroy(&data->forks[i].mutex);
			pthread_mutex_destroy(&data->m_tab[READY]);
			pthread_mutex_destroy(&data->m_tab[PRINT]);
			pthread_mutex_destroy(&data->m_tab[DEAD]);
			return (error_msg(MUTEX), 1);
		}
	}
	return (0);
}

int	ft_init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->m_tab[READY], NULL))
		return (error_msg(MUTEX), 1);
	if (pthread_mutex_init(&data->m_tab[PRINT], NULL))
	{
		pthread_mutex_destroy(&data->m_tab[READY]);
		return (error_msg(MUTEX), 1);
	}
	if (pthread_mutex_init(&data->m_tab[DEAD], NULL))
	{
		pthread_mutex_destroy(&data->m_tab[READY]);
		pthread_mutex_destroy(&data->m_tab[PRINT]);
		return (error_msg(MUTEX), 1);
	}
	if (ft_init_forks(data))
		return (1);
	return (0);
}

int	ft_malloc_mutexes(t_data *data)
{
	data->m_tab = malloc(sizeof(pthread_mutex_t) * 3);
	if (!data->m_tab)
		return (error_msg(MALLOC), 1);
	return (0);
}
