/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophe.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabbe <ylabbe@student.42quebec.c>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:30:01 by ylabbe            #+#    #+#             */
/*   Updated: 2022/11/26 21:19:05 by ylabbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHE_H
# define PHILOSOPHE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_rules;

typedef struct s_philo
{
	struct s_rules	*rules;
	long long		last_meal;
	pthread_t		thread_id;
	int				id;
	int				finished_meal;
	int				left_fork;
	int				right_fork;
}	t_philo;

typedef struct s_rules
{
	t_philo			philo[200];
	pthread_mutex_t	fork[250];
	pthread_mutex_t	writing;
	pthread_mutex_t	spaghetti;
	long long		initialize_timestamp;
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				nb_of_times_each_ate;
	int				dead_philosopher;
}	t_rules;

int			ft_initialisation(t_rules *rules, char **argv);
int			ft_initialisation_mutex(t_rules *rules);
int			ft_initialisation_philosophe(t_rules *rules);
int			ft_program(t_rules *rules);
void		ft_exit_program(t_rules *rules);
void		ft_die(t_rules *rules, t_philo *philo);
void		*sleep_think(void *philosopher);
void		ft_time(long long time, t_rules *rules);
void		ft_eat(t_philo *philo);
long long	ft_timestamp(void);
void		ft_log(t_rules *rules, int id, char *str);
int			ft_atoi(const char *str);

#endif
