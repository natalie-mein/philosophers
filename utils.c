/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:07:07 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/12 12:54:47 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (*str == '\0')
		ft_num_error();
	while (*str)
	{
		if (!ft_isdigit(*str))
			ft_num_error();
		n = n * 10 + *str - 48;
		str++;
	}
	if ((sign * n) > INT_MAX || (sign * n) < INT_MIN)
		ft_num_error();
	return (sign * n);
}

long	get_time(void)
{
	struct timeval	val;
	long			time;

	gettimeofday(&val, NULL);
	time = val.tv_sec * 1000 + val.tv_usec / 1000;
	return (time);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
	return (0);
}

void	print_msg(char *s, t_phil *phil, int id)
{
	size_t	time;

	pthread_mutex_lock(phil->write);
	time = get_time() - phil->routine->start;
	if (!has_died(phil))
		printf("%zu %d %s\n", time, id, s);
	pthread_mutex_unlock(phil->write);
}
