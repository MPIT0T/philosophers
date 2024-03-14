/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:30:52 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/12 18:58:14 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_data *data)
{
	free(data->forks);
	free(data->philo);
	free(data->m_tab);
}

void	destroy_all(t_data *data)
{
	pthread_mutex_destroy(&data->m_tab[READY]);
	pthread_mutex_destroy(&data->m_tab[PRINT]);
	pthread_mutex_destroy(&data->m_tab[DEAD]);
	while (data->nb_philo--)
		pthread_mutex_destroy(&data->forks[data->nb_philo].mutex);
}
