/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:10:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/22 20:42:36 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t 		thread;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_data
{
	size_t			nb_philo;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	long long		first_time;
}	t_data;

int		ft_atoi(const char *nptr);
void	ft_putstr_fd(const char *s, int fd);
size_t	ft_strlen(const char *s);

#endif
