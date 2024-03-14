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
