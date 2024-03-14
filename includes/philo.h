/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:10:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/14 22:20:53 by mpitot           ###   ########.fr       */
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

//RED		"\033[1;31m"
//GREEN		"\033[1;32m"
//YELLOW	"\033[1;33m"
//BLUE		"\033[1;34m"
//MAGENTA	"\033[1;35m"
//CYAN		"\033[1;36m"
//WHITE		"\033[1;37m"
//DEFAULT	"\033[0m"

# define MAX_PHILO 200

struct	s_data;
struct	s_fork;

typedef enum e_error
{
	ARGS,
	ARG,
	MALLOC,
	MUTEX,
	THREAD
}	t_error;

typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_action;

typedef enum e_mutex
{
	DEAD,
	READY,
	PRINT
}	t_mutex;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	struct s_fork	*l_fork;
	struct s_fork	*r_fork;
	long long		last_meal;
	size_t			meals;
	struct s_data	*data;
}				t_philo;

typedef struct s_fork
{
	int				owner;
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct s_data
{
	size_t			nb_philo;
	t_philo			*philo;
	t_fork			*forks;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		first_time;
	size_t			max_meals;
	pthread_mutex_t	*m_tab;
	bool			dead;
	bool			eated;
}				t_data;

//ROUTINE
	//pair
void		*ft_routine_pair(void *arg);
	//odd
void		*ft_routine_odd(void *arg);
	//utils
int			ft_try_lfork(t_philo *philo);
int			ft_release_lfork(t_philo *philo);
int			ft_release_rfork(t_philo *philo);
int			ft_try_rfork(t_philo *philo);
int			ft_sleep(t_philo *philo);
bool		ft_dead(t_data *data);
void		ft_make_dead(t_data *data);

//UTILS
long		ft_atol(const char *nptr);
size_t		ft_strlen(const char *s);
int			ft_isdigit(const char *str);
int			check_args(int ac, char **av);

//INIT
int			ft_init(t_data *data, char **argv);
int			ft_malloc_structs(t_data *data);
int			ft_init_mutexes(t_data *data);
int			ft_startup(t_data *data);
int			ft_check_meals(t_data *data);
void		ft_free_all(t_data *data);
void		destroy_all(t_data *data);
int			ft_malloc_mutexes(t_data *data);

//PRINT
void		ft_put_info(t_philo *philo, enum e_action action);
void		error_msg(t_error error);
void		ft_putstr_fd(const char *s, int fd);
void		ft_put_eated(t_data *data);

//TIME
long long	ft_get_time(t_data *data);
int			ft_usleep(t_philo *philo, long long time);

#endif
