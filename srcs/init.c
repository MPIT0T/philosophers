/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:33:48 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/27 17:16:56 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_init_threads(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&data->philo[i].thread, NULL, &ft_routine_pair, &data->philo[i]))
				return (error_msg(1), 1);
		}
		else
		{
			if (pthread_create(&data->philo[i].thread, NULL, &ft_routine_odd, &data->philo[i]))
				return (error_msg(1), 1);
		}
	}
	return (0);
}

int	ft_malloc_structs(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (error_msg(3), 1);
	data->forks = malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->forks)
		return (error_msg(3), free(data->philo), 1);
	return (0);
}

void	ft_fill_structs(t_data *data, size_t i)
{
	data->forks[i].owner = 0;
	data->philo[i].id = (int) i + 1;
	data->philo[i].l_fork = &data->forks[i];
	data->philo[i].r_fork = &data->forks[(i + 1) % data->nb_philo];
	data->philo[i].alive = true;
	data->philo[i].last_meal = 0;
	data->philo[i].data = data;
	data->philo[i].ready = false;
}

int	ft_init(t_data *data, int argc, char **argv)
{
	size_t	i;
	long long first_time;

	(void) argc;
	first_time = ft_get_time();
	data->nb_philo = ft_atoi(argv[1]);
	ft_malloc_structs(data);
	i = -1;
	while (++i < data->nb_philo)
		ft_fill_structs(data, i);
	data->time_to_die = atoll(argv[2]);
	data->time_to_eat = atoll(argv[3]);
	data->time_to_sleep = atoll(argv[4]);
	data->max_meals = 0;
	if (argc == 6)
		data->max_meals = atoi(argv[5]);
	data->first_time = first_time;
	data->dead = false;
	return (0);
}
