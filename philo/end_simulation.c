/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:04:42 by nseropia          #+#    #+#             */
/*   Updated: 2023/09/25 13:49:57 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_dead(t_philo *philo, long long time_to_die)
{
	pthread_mutex_lock(&philo->meal_time_lock);
	if (get_time() - philo->last_meal_time >= time_to_die
		&& philo->is_eating == 0)
	{
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_time_lock);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->sim->no_of_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].sim->time_to_die))
		{
			log_status(&philos[i], DIED);
			pthread_mutex_lock(&philos->sim->sim_stop_lock);
			philos->sim->sim_stop = 1;
			pthread_mutex_unlock(&philos->sim->sim_stop_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos[0].sim->max_meals == -1)
		return (0);
	while (i < philos->sim->no_of_philos)
	{
		pthread_mutex_lock(&philos[i].meal_time_lock);
		if (philos[i].no_of_meals_eaten >= philos[i].sim->max_meals)
			philos[i].finished_eating++;
		pthread_mutex_unlock(&philos[i].meal_time_lock);
		i++;
	}
	if (philos->finished_eating == philos->sim->no_of_philos)
	{
		pthread_mutex_lock(&philos->sim->sim_stop_lock);
		philos->sim->sim_stop = 1;
		pthread_mutex_unlock(&philos->sim->sim_stop_lock);
		return (1);
	}
	return (0);
}

void	death_monitor(t_sim *sim)
{
	while (1)
	{
		if (check_if_dead(sim->philo) == 1 || check_if_all_ate(sim->philo) == 1)
			break ;
	}
}

void	free_and_destroy(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->no_of_philos)
		pthread_join(sim->philo[i].thread, NULL);
	i = -1;
	while (++i < sim->no_of_philos)
	{
		pthread_mutex_destroy(&sim->philo[i].meal_time_lock);
		pthread_mutex_destroy(&sim->forks_lock[i]);
	}
	pthread_mutex_destroy(&sim->write_lock);
	pthread_mutex_destroy(&sim->sim_stop_lock);
	free(sim->philo);
	free(sim->forks_lock);
}
