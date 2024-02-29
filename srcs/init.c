/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:33:48 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/29 18:29:35 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_init_mutexes(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->forks[i].owner = 0;
		data->forks[i].mutex = malloc(sizeof(pthread_mutex_t));
		if ()
		if (pthread_mutex_init(data->forks[i].mutex, NULL))
			return (error_msg(4), 1);
	}
	return (0);
}

void	ft_fill_structs(t_data *data, t_philo *philo, size_t i)
{
	(*philo).id = (int) i + 1;
	(*philo).l_fork = &data->forks[i];
	(*philo).r_fork = &data->forks[(i + 1) % data->nb_philo];
	(*philo).alive = true;
	(*philo).last_meal = 0;
	(*philo).data = data;
	(*philo).ready = false;
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
		ft_fill_structs(data, &data->philo[i], i);
	data->time_to_die = atoll(argv[2]);	//TODO remove atoll
	data->time_to_eat = atoll(argv[3]);
	data->time_to_sleep = atoll(argv[4]);
	data->max_meals = 0;
	if (argc == 6)
		data->max_meals = atoi(argv[5]);
	data->first_time = first_time;
	data->dead = false;
	ft_init_mutexes(data);
	return (0);
}
