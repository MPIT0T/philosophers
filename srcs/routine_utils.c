/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:40:24 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/28 18:00:35 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*

bool	everyone_ready(t_data **data)
{
	size_t i;

	i = -1;
	while (++i < (*data)->nb_philo)
	{
		if (!(*data)->philo[i].ready)
			return (false);
	}
	return (true);
}
*/

void	ft_sleep(t_philo *philo)
{
	ft_put_info(philo, "is sleeping");
	ft_usleep(philo, philo->data->time_to_sleep);
}