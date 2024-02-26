/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:08:13 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/22 23:33:37 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_put_info(t_philo *philo, const char *str, t_data *data)
{
	struct timeval time;
	long long		time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = (time.tv_usec / 1000 + time.tv_sec * 1000) - data->first_time;
	printf("%lli", time_in_ms);
	ft_putstr_fd("test", 1);
	ft_putstr_fd(str, 1);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_putstr_fd("has taken a fork\n", 1);
		pthread_mutex_lock(philo->right_fork);
		ft_putstr_fd("has taken a fork\n", 1);
		ft_putstr_fd("is eating\n", 1);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_putstr_fd("is sleeping\n", 1);
		ft_putstr_fd("is thinking\n", 1);
	}
	return (NULL);
}

int	ft_init_threads(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &ft_routine, &data->philo[i]))
		{
			ft_putstr_fd("Error: pthread_create failed\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_init(t_data *data, int argc, char **argv)
{
	size_t	i;

	(void) argc;
	data->nb_philo = ft_atoi(argv[1]);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		free(data->philo);
		return (1);
	}
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
	}
	return (0);
}

int	ft_print_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	printf("%li", time.tv_usec / 1000 + time.tv_sec * 1000);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data data;
	struct timeval first_time;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	gettimeofday(&first_time, NULL);
	data.first_time = first_time.tv_usec / 1000 + first_time.tv_sec * 1000;
	if (ft_init(&data, argc, argv))
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	ft_print_time();
	return (0);
}
