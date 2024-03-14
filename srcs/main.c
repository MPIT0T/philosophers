/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:08:13 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/12 18:59:51 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	ft_init(t_data *data, int argc, char **argv)
{
	size_t	i;

	(void) argc;
	data->nb_philo = ft_atol(argv[1]);
	if (ft_malloc_structs(data))
		return (1);
	i = -1;
	while (++i < data->nb_philo)
		ft_fill_structs(data, &data->philo[i], i);
	data->first_time = 0;
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->max_meals = 0;
	if (argc == 6)
		data->max_meals = ft_atol(argv[5]);
	data->dead = false;
	if (ft_init_mutexes(data))
		return (1);
	return (0);
}*/

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	if (ft_init(&data, argv))
		return (1);
	if (ft_startup(&data))
		return (destroy_all(&data), ft_free_all(&data), 1);
	if (ft_check_meals(&data))
		ft_put_eated(&data);
	destroy_all(&data);
	ft_free_all(&data);
	return (0);
}
