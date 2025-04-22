/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:55:49 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/19 11:48:38 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_dead(t_phil *phil)
{
	pthread_mutex_lock(&phil->meal);
	if ((get_time() - phil->last_meal) >= phil->routine->die_t
		&& phil->eating == 0)
		return (pthread_mutex_unlock(&phil->meal), 1);
	pthread_mutex_unlock(&phil->meal);
	return (0);
}

int	death_check(t_routine *routine)
{
	int	i;

	i = 0;
	while (i < routine->num)
	{
		if (philo_dead(&routine->phil[i]) == 1)
		{
			print_msg("died", &routine->phil[i], routine->phil[i].id);
			pthread_mutex_lock(&routine->dead_mutex);
			routine->dead_flag = 1;
			pthread_mutex_unlock(&routine->dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	meals_check(t_routine *routine)
{
	int	i;
	int	done_eating;

	i = 0;
	done_eating = 0;
	if (routine->eat_max == -1)
		return (0);
	while (i < routine->num)
	{
		pthread_mutex_lock(&routine->phil[i].meal);
		if (routine->phil[i].n_meals >= routine->eat_max)
			done_eating++;
		pthread_mutex_unlock(&routine->phil[i].meal);
		i++;
	}
	pthread_mutex_lock(&routine->dead_mutex);
	if (done_eating >= routine->num)
	{
		routine->dead_flag = 1;
		pthread_mutex_unlock(&routine->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&routine->dead_mutex);
	return (0);
}

void	*monitor(void *ptr)
{
	t_routine	*routine;

	routine = (t_routine *)ptr;
	while (1)
	{
		usleep(1);
		if (death_check(routine) == 1 || meals_check(routine) == 1)
			break ;
	}
	return (ptr);
}
