/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:30:52 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/29 18:31:12 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		free(data->forks[i].mutex);
	}
	free(data->philo);

	return ;
}
