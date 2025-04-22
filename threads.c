/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:58:21 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/19 11:50:42 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_exit(t_routine *routine, int num)
{
	int	i;

	i = 0;
	while (i <= num)
	{
		if (pthread_join(routine->phil[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	join_threads(t_routine *routine)
{
	int	i;

	i = 0;
	while (i < routine->num)
	{
		pthread_join(routine->phil[i].thread, NULL);
		i++;
	}
}

int	init_threads(t_routine *routine)
{
	int			i;
	pthread_t	watchman;

	i = 0;
	routine->start = get_time();
	if (pthread_create(&watchman, NULL, &monitor, (void *)routine) != 0)
		return (0);
	while (i < routine->num)
	{
		if (pthread_create(&routine->phil[i].thread, NULL,
				&phil_routine, (void *)&routine->phil[i]))
		{
			join_exit(routine, i);
			return (0);
		}
		i++;
	}
	join_threads(routine);
	pthread_join(watchman, NULL);
	return (1);
}
