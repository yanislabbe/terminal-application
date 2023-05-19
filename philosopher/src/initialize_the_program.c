/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_the_program.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabbe <ylabbe@student.42quebec.c>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:37:49 by ylabbe            #+#    #+#             */
/*   Updated: 2022/11/26 21:19:46 by ylabbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophe.h"

int	ft_atoi(const char *str)
{
	int	nombre;

	nombre = 0;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			nombre = nombre * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(nombre));
}

int	ft_initialisation_philosophe(t_rules *rules)
{
	int	number;

	number = rules->nb_of_philo + 1;
	while (--number >= 0)
	{
		rules->philo[number].id = number;
		rules->philo[number].finished_meal = 0;
		rules->philo[number].left_fork = number;
		rules->philo[number].right_fork = (number + 1) % rules->nb_of_philo;
		rules->philo[number].last_meal = 0;
		rules->philo[number].rules = rules;
	}
	return (0);
}

int	ft_initialisation_mutex(t_rules *rules)
{
	int	number;

	number = rules->nb_of_philo;
	while (--number >= 0)
		if (pthread_mutex_init(&(rules->fork[number]), NULL))
			return (1);
	if (pthread_mutex_init(&(rules->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->spaghetti), NULL))
		return (1);
	return (0);
}

int	ft_initialisation(t_rules *rules, char **argv)
{
	rules->nb_of_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->nb_of_times_each_ate = 0;
	rules->dead_philosopher = 0;
	if (rules->nb_of_philo < 1 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0
		|| rules->nb_of_philo > 200)
		return (1);
	if (argv[5])
	{
		rules->nb_must_eat = ft_atoi(argv[5]);
		if (rules->nb_must_eat <= 0)
			return (1);
	}
	else
		rules->nb_must_eat = -1;
	if (ft_initialisation_mutex(rules))
		return (1);
	ft_initialisation_philosophe(rules);
	return (0);
}
