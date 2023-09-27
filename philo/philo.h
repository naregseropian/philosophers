/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:48:37 by NaregSeropi       #+#    #+#             */
/*   Updated: 2023/09/27 12:12:41 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo	t_philo;

typedef struct s_sim {
	int				no_of_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		max_meals;
	int				sim_stop;
	long long		start_time;
	int				all_ate;
	t_philo			*philo;
	pthread_mutex_t	*forks_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	sim_stop_lock;
}	t_sim;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	int				no_of_meals_eaten;
	long long		last_meal_time;
	int				finished_eating;
	int				is_eating;
	int				r_fork;
	int				l_fork;
	pthread_mutex_t	meal_time_lock;
	t_sim			*sim;
}	t_philo;

typedef enum e_error_type {
	ERR_USAGE,
	ERR_INPUT,
}	t_error_type;

typedef enum e_act
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED
}	t_act;

// check_args c
int			ft_strcheck(char *str);

// error_handling c
int			error_msg(t_error_type type, int exit_no);

// init.c
int			init_sim(int argc, char **argv, t_sim *sim);
void		init_philos(t_sim *sim);

// end_simulation.c
int			philosopher_dead(t_philo *philo, long long time_to_die);
int			check_if_dead(t_philo *philos);
int			check_if_all_ate(t_philo *philos);
void		death_monitor(t_sim *sim);
void		free_and_destroy(t_sim *sim);

// actions.c
void		ft_think(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);

// routine.c
void		*routine(void *param);
int			is_terminated(t_philo *philo);

// utils.c
long long	get_time(void);
void		log_status(t_philo *philo, t_act act);
int			ft_usleep(size_t milliseconds);

// main.c
void		launch_threads(t_sim *sim);
int			check_if_all_ate(t_philo *philos);

#endif
