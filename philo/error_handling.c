/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:35:51 by nseropia          #+#    #+#             */
/*   Updated: 2023/09/24 17:08:30 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(t_error_type type, int exit_no)
{
	if (type == ERR_USAGE)
		printf("philo: usage: "
			"./philo <number_of_philosophers> <time_to_die> <time_to_eat>" 
			"<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
	else if (type == ERR_INPUT)
		printf("philo: invalid input: "
			"Only numeric, non-negative, non-zero, int range args.\n");
	return (exit_no);
}
