/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:34:58 by nseropia          #+#    #+#             */
/*   Updated: 2023/09/27 12:41:02 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_terminated(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->sim_stop_lock);
	if (philo->sim->sim_stop == 1)
	{
		pthread_mutex_unlock(&philo->sim->sim_stop_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->sim_stop_lock);
	return (0);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_terminated(philo))
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
