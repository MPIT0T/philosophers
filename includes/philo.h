/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:10:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/27 18:00:01 by mpitot           ###   ########.fr       */
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

struct s_data;
struct s_fork;

typedef struct s_philo
{
	pthread_t 		thread;
	int				id;
	struct s_fork	*l_fork;
	struct s_fork	*r_fork;
	bool			alive;
	long long		last_meal;
	struct s_data	*data;
	bool			ready;
}	t_philo;

typedef struct s_fork
{
	int				owner;
	pthread_mutex_t *mutex;
}	t_fork;

typedef struct s_data
{
	size_t			nb_philo;
	t_philo			*philo;
	t_fork			*forks;
	pthread_mutex_t	*print;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		first_time;
	size_t			max_meals;
	bool			dead;
}	t_data;


//ROUTINE
	//pair
void		*ft_routine_pair(void *arg);
	//odd
void		*ft_routine_odd(void *arg);
	//utils
int			ft_try_lfork(t_philo *philo);
int			ft_try_rfork(t_philo *philo);
bool		everyone_ready(t_data *data);
void		ft_sleep(t_philo *philo);


//UTILS
int			ft_atoi(const char *nptr);
size_t		ft_strlen(const char *s);

//INIT
int			ft_init_threads(t_data *data);
int			ft_init(t_data *data, int argc, char **argv);
int			ft_malloc_structs(t_data *data);
void		ft_fill_structs(t_data *data, size_t i);


//PRINT
void		ft_put_info(t_philo *philo, const char *str);
void		error_msg(int error);
void		ft_putstr_fd(const char *s, int fd);

//TIME
long long	ft_get_time(void);
void		ft_usleep(t_philo *philo, long long time);

#endif