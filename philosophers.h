/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:58:27 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/12 12:45:14 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_phil
{
	pthread_t			thread;
	int					id;
	long				last_meal;
	int					n_meals;
	int					eating;
	struct s_routine	*routine;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*write;
	pthread_mutex_t		meal;
}	t_phil;

typedef struct s_routine
{
	int				num;
	long			die_t;
	int				eat_t;
	int				sleep_t;
	int				eat_max;
	long			start;
	int				dead_flag;
	t_phil			*phil;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	write;
}				t_routine;

// init
int		init_table(t_routine *routine, int ac, char **av);
int		init_routine(t_routine *routine, int ac, char **av);
int		init_philosophers(t_routine *routine);
int		init_threads(t_routine *routine);
int		init_forks(t_routine *routine);

// routine
void	*phil_routine(void *arg);
void	join_threads(t_routine *routine);

// monitor
int		has_died(t_phil *phil);
int		dead_philo(t_phil *phil, size_t t_die);
int		meals_check(t_routine *routine);
void	*monitor(void *ptr);

// exit
void	ft_error(void);
void	ft_num_error(void);
void	ft_neg_error(void);
void	destroy_resources(t_routine *routine);
void	free_resources(t_routine *routine);
int		forks_error(t_routine *routine);

// utils
int		ft_atoi(const char *str);
long	get_time(void);
int		ft_usleep(size_t ms);
void	print_msg(char *s, t_phil *phil, int id);

#endif
