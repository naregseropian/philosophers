/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:35:44 by nseropia          #+#    #+#             */
/*   Updated: 2023/09/24 17:10:56 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcheck(char *str)
{
	long long	res;
	int			i;

	i = 0;
	res = 0;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res = (res * 10) + (str[i] - '0');
			i++;
		}
		else
			return (-1);
	}
	if (res > INT_MAX || res == 0)
		return (-1);
	return ((int)res);
}
