/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:33:48 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/04 16:12:20 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_threads(t_data *data)
{
	size_t	i;

	i = -1;
	pthread_mutex_lock(data->ready);
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
	pthread_mutex_unlock(data->ready);
	data->first_time = 0;
	data->first_time = ft_get_time(data);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philo[i].thread, NULL);
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

	data->ready = malloc(sizeof(pthread_mutex_t));
	data->print = malloc(sizeof(pthread_mutex_t));
	data->time = malloc(sizeof(pthread_mutex_t));
	data->m_dead = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->ready, NULL) || pthread_mutex_init(data->print, NULL) || pthread_mutex_init(data->m_dead, NULL))
		return (error_msg(4), 1);
	i = -1;
	while (++i < data->nb_philo)
	{
		data->forks[i].owner = 0;
		data->forks[i].mutex = malloc(sizeof(pthread_mutex_t));
		data->philo[i].m_alive = malloc(sizeof(pthread_mutex_t));
		data->philo[i].m_last_meal = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(data->forks[i].mutex, NULL) || pthread_mutex_init(data->philo[i].m_alive, NULL) || pthread_mutex_init(data->philo[i].m_last_meal, NULL))
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
}

int	ft_init(t_data *data, int argc, char **argv)
{
	size_t	i;

	(void) argc;
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
	data->dead = false;
	ft_init_mutexes(data);
	return (0);
}
