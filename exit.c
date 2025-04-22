/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:59:40 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/14 11:44:04 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error(void)
{
	printf("Please enter:\n \t1. A number of philosophers,\n");
	printf(" \t2. A time to die,\n");
	printf("\t3. A time to eat.\n \t4. And a time to sleep\n");
	printf("\tYou may also enter: 5. the number of times\n");
	printf("\tyou want each philosopher to eat.\n");
	exit (EXIT_FAILURE);
}

void	ft_num_error(void)
{
	printf("Please ensure the values you enter are integers.\n");
	printf("They should be POSITIVE integers:\n");
	printf("Smaller than 2147483647(INT_MAX)\n");
	printf("and larger than zero (0).\n");
	exit (EXIT_FAILURE);
}

void	free_resources(t_routine *routine)
{
	if (routine->phil)
		free(routine->phil);
	if (routine->forks)
		free(routine->forks);
}
