/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:41:48 by nseropia          #+#    #+#             */
/*   Updated: 2023/09/25 13:50:34 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->no_of_philos)
		pthread_mutex_init(&sim->forks_lock[i], NULL);
	i = -1;
	while (++i < sim->no_of_philos)
	{
		pthread_mutex_init(&sim->philo[i].meal_time_lock, NULL);
		sim->philo[i].id = i;
		sim->philo[i].no_of_meals_eaten = 0;
		sim->philo[i].last_meal_time = get_time();
		sim->philo[i].finished_eating = 0;
		sim->philo[i].is_eating = 0;
		sim->philo[i].sim = sim;
		sim->philo[i].l_fork = i;
		if (i == 0)
			sim->philo[i].r_fork = sim->no_of_philos - 1;
		else
			sim->philo[i].r_fork = i - 1;
	}
}

int	init_sim(int argc, char **argv, t_sim *sim)
{
	sim->no_of_philos = ft_strcheck(argv[1]);
	sim->time_to_die = ft_strcheck(argv[2]);
	sim->time_to_eat = ft_strcheck(argv[3]);
	sim->time_to_sleep = ft_strcheck(argv[4]);
	sim->max_meals = -1;
	if (sim->no_of_philos == -1 || sim->time_to_die == -1
		|| sim->time_to_eat == -1 || sim->time_to_sleep == -1)
		return (0);
	if (argc == 6 && ft_strcheck(argv[5]) != -1)
		sim->max_meals = ft_strcheck(argv[5]);
	else if (argc == 6)
		return (0);
	sim->sim_stop = 0;
	sim->start_time = get_time();
	sim->all_ate = 0;
	sim->philo = malloc(sizeof(t_philo) * sim->no_of_philos);
	if (!sim->philo)
		return (0);
	sim->forks_lock = malloc(sizeof(pthread_mutex_t) * sim->no_of_philos);
	if (!sim->forks_lock)
		return (free(sim->philo), 0);
	pthread_mutex_init(&sim->write_lock, NULL);
	pthread_mutex_init(&sim->sim_stop_lock, NULL);
	init_philos(sim);
	return (1);
}
