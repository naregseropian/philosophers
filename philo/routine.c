/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:34:58 by nseropia          #+#    #+#             */
/*   Updated: 2023/09/26 17:27:38 by nseropia         ###   ########.fr       */
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

/* here, we are running this routine until a philo is dead or all of them are
full. For all of them to be full, we need each thread to increment the variable
all_eaten by one each time their eat count has reached max_meal. Once all_eaten
== no_of_philo we can then make the sim_stop to one*/
/* or do we? isn't that monitor's job??? what is the while condition of the 
philo routine? 
the monitor's job, as it's name indicates only checks if that number is 1
the routine increments and runs if not terminated*/
void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_terminated(philo))
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
