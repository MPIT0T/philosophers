/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:33:48 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/14 18:55:44 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_malloc_structs(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (error_msg(MALLOC), 1);
	data->forks = malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->forks)
		return (error_msg(MALLOC), free(data->philo), 1);
	return (0);
}

void	ft_fill_philo(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].id = (int) i + 1;
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philo[i].last_meal = 0;
		data->philo[i].meals = 0;
		data->philo[i].data = data;
	}
}

void	ft_fill_data(t_data *data, char **argv)
{
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->dead = false;
	data->first_time = 0;
	if (argv[5])
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = 0;
}

int	ft_init(t_data *data, char **argv)
{
	data->nb_philo = ft_atol(argv[1]);
	if (ft_malloc_structs(data))
		return (1);
	ft_fill_data(data, argv);
	ft_fill_philo(data);
	ft_malloc_mutexes(data);
	ft_init_mutexes(data);
	return (0);
}
