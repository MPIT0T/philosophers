/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:08:13 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/27 15:45:06 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 5 && argc != 6)
		return (error_msg(1), 1);
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