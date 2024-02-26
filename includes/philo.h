/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:10:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/26 21:29:24 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t 		thread;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	bool			alive;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		last_meal;
	long long		first_time;
}	t_philo;

typedef struct s_data
{
	size_t			nb_philo;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}	t_data;

int		ft_atoi(const char *nptr);
void	ft_putstr_fd(const char *s, int fd);
size_t	ft_strlen(const char *s);

void	error_msg(int error);
long long ft_get_time(void);

#endif
