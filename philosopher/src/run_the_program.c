/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_the_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabbe <ylabbe@student.42quebec.c>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:18:56 by ylabbe            #+#    #+#             */
/*   Updated: 2022/11/26 21:18:48 by ylabbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophe.h"

void	ft_die(t_rules *rules, t_philo *philo)
{
	int	x;

	while (!(rules->nb_of_times_each_ate))
	{
		x = -1;
		while (++x < rules->nb_of_philo && !(rules->dead_philosopher))
		{
			pthread_mutex_lock(&(rules->spaghetti));
			if (((ft_timestamp()) - (philo[x].last_meal)) > rules->time_to_die)
			{
				ft_log(rules, x, "died");
				rules->dead_philosopher = 1;
				pthread_mutex_unlock(&rules->spaghetti);
				return ;
			}
			pthread_mutex_unlock(&(rules->spaghetti));
			usleep(100);
		}
		x = 0;
		while (rules->nb_must_eat != -1
			&& philo[x].finished_meal >= rules->nb_must_eat - 1)
			x++;
		if (x == rules->nb_of_philo)
			rules->nb_of_times_each_ate = 1;
	}
}

void	*sleep_think(void *philosopher)
{
	t_philo	*philo;
	t_rules	*rules;
	int		x;

	x = 0;
	philo = (t_philo *)philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->dead_philosopher))
	{
		ft_eat(philo);
		if (rules->nb_of_times_each_ate)
			break ;
		ft_log(rules, philo->id, "is sleeping");
		ft_time(rules->time_to_sleep, rules);
		ft_log(rules, philo->id, "is thinking");
		x++;
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->fork[philo->left_fork]));
	ft_log(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->fork[philo->right_fork]));
	ft_log(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->spaghetti));
	ft_log(rules, philo->id, "is eating");
	philo->last_meal = ft_timestamp();
	pthread_mutex_unlock(&(rules->spaghetti));
	ft_time(rules->time_to_eat, rules);
	(philo->finished_meal)++;
	pthread_mutex_unlock(&rules->fork[philo->left_fork]);
	pthread_mutex_unlock(&rules->fork[philo->right_fork]);
}

void	ft_exit_program(t_rules *rules)
{
	int	number;

	number = rules->nb_of_philo;
	while (--number >= 0)
		pthread_mutex_destroy(&(rules->fork[number]));
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&(rules->spaghetti));
}

int	ft_program(t_rules *rules)
{
	t_philo	*philo;
	int		x;

	philo = rules->philo;
	x = 0;
	rules->initialize_timestamp = ft_timestamp();
	while (x < rules->nb_of_philo)
	{
		pthread_create(&(philo[x].thread_id), NULL, sleep_think, &(philo[x]));
		philo[x].last_meal = ft_timestamp();
		x++;
	}
	ft_die(rules, rules->philo);
	while (x-- && rules->nb_of_philo > 1)
		pthread_join(philo[x].thread_id, NULL);
	if (rules->nb_of_philo > 1)
		ft_exit_program(rules);
	return (0);
}
