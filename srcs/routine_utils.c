/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:40:24 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/23 20:27:47 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo)
{
	ft_put_info(philo, SLEEP);
	if (ft_usleep(philo, philo->data->time_to_sleep))
		return (1);
//	usleep(500);
	return (0);
}

bool	ft_dead(t_data *data)
{
	bool	x;

	pthread_mutex_lock(&data->m_tab[DEAD]);
	x = data->dead;
	pthread_mutex_unlock(&data->m_tab[DEAD]);
	return (x);
}

void	ft_make_dead(t_data *data)
{
	pthread_mutex_lock(&data->m_tab[DEAD]);
	data->dead = true;
	pthread_mutex_unlock(&data->m_tab[DEAD]);
}
