/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:40:47 by nseropia          #+#    #+#             */
/*   Updated: 2023/09/27 12:39:17 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * get_time - Returns the current time in milliseconds since the epoch.
 *
 * This function makes use of gettimeofday, which provides the time in
 * seconds and microseconds since the epoch. The returned value represents
 * the time in milliseconds.
 *
 * Note: gettimeofday can be affected by discontinuous jumps in the system
 * time (e.g., manual changes to the clock), so it may not be ideal for
 * measuring time intervals.
 *
 * Return: time in milliseconds since the epoch.
 */
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
	return (0);
}

void	log_status(t_philo *philo, t_act act)
{
	long	ms;

	pthread_mutex_lock(&philo->sim->write_lock);
	ms = get_time() - philo->sim->start_time;
	if (act == FORK && !is_terminated(philo))
		printf("%ld %d has taken a fork\n", ms, philo->id + 1);
	if (act == EAT && !is_terminated(philo))
		printf("%ld %d is eating\n", ms, philo->id + 1);
	if (act == SLEEP && !is_terminated(philo))
		printf("%ld %d is sleeping\n", ms, philo->id + 1);
	if (act == THINK && !is_terminated(philo))
		printf("%ld %d is thinking\n", ms, philo->id + 1);
	if (act == DIED && !is_terminated(philo))
		printf("%ld %d died\n", ms, philo->id + 1);
	pthread_mutex_unlock(&philo->sim->write_lock);
}
