/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:22:05 by nseropia          #+#    #+#             */
/*   Updated: 2023/09/27 12:44:56 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_philo *philo)
{
	log_status(philo, THINK);
}

void	ft_sleep(t_philo *philo)
{
	log_status(philo, SLEEP);
	ft_usleep(philo->sim->time_to_sleep);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->forks_lock[philo->l_fork]);
	log_status(philo, (t_act) FORK);
	if (philo->sim->no_of_philos == 1)
	{
		ft_usleep(philo->sim->time_to_die);
		pthread_mutex_unlock(&philo->sim->forks_lock[philo->l_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->sim->forks_lock[philo->r_fork]);
	log_status(philo, (t_act) FORK);
	philo->is_eating = 1;
	log_status(philo, (t_act) EAT);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal_time = get_time();
	philo->no_of_meals_eaten++;
	pthread_mutex_unlock(&philo->meal_time_lock);
	ft_usleep(philo->sim->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->sim->forks_lock[philo->r_fork]);
	pthread_mutex_unlock(&philo->sim->forks_lock[philo->l_fork]);
}
