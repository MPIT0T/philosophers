/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:08:13 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/26 22:48:09 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_put_info(t_philo *philo, const char *str)
{
	long long	time_in_ms;

	time_in_ms = ft_get_time() - philo->first_time;
	printf("%lli %d %s\n", time_in_ms, philo->id, str);
}

void	*ft_routine_odd(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->alive)
	{
		pthread_mutex_lock(philo->left_fork);
		if (philo->last_meal != 0 && ft_get_time() - philo->last_meal > philo->time_to_die)
			return (ft_put_info(philo, "died"), philo->alive = false, NULL);
		ft_put_info(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		ft_put_info(philo, "has taken a fork");
		ft_put_info(philo, "is eating");
		usleep(philo->time_to_eat * 1000);
		philo->last_meal = ft_get_time();
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_put_info(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		ft_put_info(philo, "is thinking");
	}
	return (NULL);
}

void	*ft_routine_pair(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->alive)
	{
		pthread_mutex_lock(philo->right_fork);
		if (philo->last_meal != 0 && ft_get_time() - philo->last_meal > philo->time_to_die)
			return (ft_put_info(philo, "died"), philo->alive = false, NULL);
		ft_put_info(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		ft_put_info(philo, "has taken a fork");
		ft_put_info(philo, "is eating");
		usleep(philo->time_to_eat * 1000);
		philo->last_meal = ft_get_time();
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		ft_put_info(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		ft_put_info(philo, "is thinking");
	}
	return (NULL);
}

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

int	ft_init(t_data *data, int argc, char **argv)
{
	size_t	i;
	long long first_time;

	(void) argc;
	first_time = ft_get_time();
	data->nb_philo = ft_atoi(argv[1]);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (free(data->philo), 1);
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].id = (int) i + 1;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philo[i].alive = true;
		data->philo[i].time_to_die = ft_atoi(argv[2]);
		data->philo[i].time_to_eat = ft_atoi(argv[3]);
		data->philo[i].time_to_sleep = ft_atoi(argv[4]);
		data->philo[i].first_time = first_time;
		data->philo[i].last_meal = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (ft_init(&data, argc, argv))
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	if (ft_init_threads(&data))
	{
		printf("Error: thread creation failed\n");
		return (1);
	}
	return (0);
}
