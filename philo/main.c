/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:35:11 by nseropia          #+#    #+#             */
/*   Updated: 2023/09/27 12:39:04 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_threads(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->no_of_philos)
	{
		pthread_create(&sim->philo[i].thread, NULL, &routine, &sim->philo[i]);
	}
	death_monitor(sim);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc != 5 && argc != 6)
		return (error_msg(ERR_USAGE, EXIT_FAILURE));
	if (!init_sim(argc, argv, &sim))
		return (error_msg(ERR_INPUT, EXIT_FAILURE));
	launch_threads(&sim);
	free_and_destroy(&sim);
	return (EXIT_SUCCESS);
}
