/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:33:26 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/19 11:49:30 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_resources(t_routine *routine)
{
	int	i;

	i = 0;
	while (i < routine->num)
	{
		pthread_mutex_destroy(&routine->forks[i]);
		pthread_mutex_destroy(&routine->phil[i].meal);
		i++;
	}
	pthread_mutex_destroy(&routine->write);
	pthread_mutex_destroy(&routine->dead_mutex);
}

int	mutex_fail(t_routine *routine)
{
	int	i;

	i = 0;
	while (i < routine->num)
	{
		pthread_mutex_destroy(&routine->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&routine->write);
	pthread_mutex_destroy(&routine->dead_mutex);
	return (0);
}

int	forks_error(t_routine *routine)
{
	pthread_mutex_destroy(&routine->write);
	pthread_mutex_destroy(&routine->dead_mutex);
	return (0);
}
