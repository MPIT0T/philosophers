/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:33:48 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/14 16:35:07 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*

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

int	ft_init_threads(t_data *data)
{
	size_t	i;

	i = -1;
	pthread_mutex_lock(data->ready);
	if (ft_create_threads(data))
	{
		pthread_mutex_unlock(data->ready);
		return (1);
	}
	data->first_time = ft_get_time(data);
	pthread_mutex_unlock(data->ready);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philo[i].thread, NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (data->philo[i].meals != data->max_meals)
			break ;
	}
	if (i == data->nb_philo)
		ft_put_eated(data);
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
	if (!data->ready)
		return (error_msg(MALLOC), 1);
	data->print = malloc(sizeof(pthread_mutex_t));
	if (!data->print)
		return (error_msg(MALLOC), free(data->ready), 1);
	data->m_dead = malloc(sizeof(pthread_mutex_t));
	if (!data->m_dead)
		return (error_msg(MALLOC), free(data->ready), free(data->print), 1);
	if (pthread_mutex_init(data->ready, NULL)
		|| pthread_mutex_init(data->print, NULL)
		|| pthread_mutex_init(data->m_dead, NULL))
		return (error_msg(MALLOC), 1);
	i = -1;
	while (++i < data->nb_philo)
	{
		data->forks[i].owner = 0;
		data->forks[i].mutex = malloc(sizeof(pthread_mutex_t));
		data->philo[i].m_alive = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(data->forks[i].mutex, NULL)
			|| pthread_mutex_init(data->philo[i].m_alive, NULL))
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
	(*philo).meals = 0;
}
*/

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
		data->philo[i].alive = true;
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
