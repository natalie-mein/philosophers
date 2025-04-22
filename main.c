/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:14:49 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/19 11:46:52 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_routine *routine)
{
	int	i;

	routine->forks = malloc(sizeof(pthread_mutex_t) * routine->num);
	if (!routine->forks)
		return (0);
	i = 0;
	while (i < routine->num)
	{
		if (pthread_mutex_init(&routine->forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

int	init_philosophers(t_routine *routine)
{
	int	i;

	i = 0;
	routine->phil = malloc(sizeof(t_phil) * routine->num);
	if (!routine->phil)
		return (0);
	while (i < routine->num)
	{
		routine->phil[i].id = i + 1;
		routine->phil[i].n_meals = 0;
		routine->phil[i].routine = routine;
		routine->phil[i].r_fork = &routine->forks[i];
		routine->phil[i].l_fork = &routine->forks[(i + 1) % routine->num];
		routine->phil[i].routine = routine;
		routine->phil[i].last_meal = get_time();
		routine->phil[i].eating = 0;
		routine->phil[i].write = &routine->write;
		if (pthread_mutex_init(&routine->phil[i].meal, NULL))
			return (0);
		i++;
	}
	return (1);
}

int	init_table(t_routine *r, int ac, char **av)
{
	r->num = ft_atoi(av[1]);
	r->die_t = ft_atoi(av[2]);
	r->eat_t = ft_atoi(av[3]);
	r->sleep_t = ft_atoi(av[4]);
	if (r->num <= 0 || r->die_t <= 0 || r->eat_t <= 0 || r->sleep_t <= 0)
		ft_num_error();
	if (ac == 6)
	{
		r->eat_max = ft_atoi(av[5]);
		if (r->eat_max <= 0)
			ft_num_error();
	}
	else
		r->eat_max = -1;
	if (pthread_mutex_init(&r->dead_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&r->write, NULL))
	{
		pthread_mutex_destroy(&r->dead_mutex);
		return (0);
	}
	if (!init_forks(r))
		return (0);
	r->dead_flag = 0;
	return (1);
}

int	main(int ac, char **av)
{
	t_routine	routine;

	if (ac < 5 || ac > 6)
		ft_error();
	if (!init_table(&routine, ac, av))
	{
		forks_error(&routine);
		return (EXIT_FAILURE);
	}
	if (!init_philosophers(&routine))
	{
		free (routine.forks);
		return (EXIT_FAILURE);
	}
	if (!init_threads(&routine))
	{
		destroy_resources(&routine);
		free_resources(&routine);
		return (EXIT_FAILURE);
	}
	destroy_resources(&routine);
	free_resources(&routine);
	return (0);
}
