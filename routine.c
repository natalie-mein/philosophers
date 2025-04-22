/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:22:23 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/12 12:57:44 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	is_eating(t_phil *phil)
{
	pthread_mutex_lock(phil->r_fork);
	print_msg("has taken a fork", phil, phil->id);
	if (phil->routine->num == 1)
	{
		ft_usleep(phil->routine->die_t);
		pthread_mutex_unlock(phil->r_fork);
		return ;
	}
	pthread_mutex_lock(phil->l_fork);
	print_msg("has taken a fork", phil, phil->id);
	print_msg("is eating", phil, phil->id);
	pthread_mutex_lock(&phil->meal);
	phil->eating = 1;
	phil->last_meal = get_time();
	phil->n_meals++;
	pthread_mutex_unlock(&phil->meal);
	ft_usleep(phil->routine->eat_t);
	phil->eating = 0;
	pthread_mutex_unlock(phil->l_fork);
	pthread_mutex_unlock(phil->r_fork);
}

void	is_sleeping(t_phil *phil)
{
	print_msg("is sleeping", phil, phil->id);
	ft_usleep(phil->routine->sleep_t);
}

void	is_thinking(t_phil *phil)
{
	print_msg("is thinking", phil, phil->id);
}

int	has_died(t_phil *phil)
{
	pthread_mutex_lock(&(phil->routine->dead_mutex));
	if (phil->routine->dead_flag == 1)
	{
		pthread_mutex_unlock(&phil->routine->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&phil->routine->dead_mutex);
	return (0);
}

void	*phil_routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	if (phil->id % 2 != 0 && phil->routine->num != 1)
	{
		is_thinking(phil);
		ft_usleep(10);
	}
	while (!has_died(phil))
	{
		if (has_died(phil))
			return (0);
		is_eating(phil);
		if (has_died(phil))
			return (0);
		is_sleeping(phil);
		if (has_died(phil))
			return (0);
		is_thinking(phil);
	}
	return (NULL);
}
