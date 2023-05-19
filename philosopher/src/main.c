/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabbe <ylabbe@student.42quebec.c>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:46:38 by ylabbe            #+#    #+#             */
/*   Updated: 2022/11/26 21:16:46 by ylabbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophe.h"

long long	ft_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_log(t_rules *rules, int id, char *str)
{
	pthread_mutex_lock(&(rules->writing));
	if (!(rules->dead_philosopher))
	{
		printf("%lli ", ft_timestamp() - rules->initialize_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(rules->writing));
	return ;
}

void	ft_time(long long time, t_rules *rules)
{
	long long	x_time;

	x_time = ft_timestamp();
	while (!(rules->dead_philosopher))
	{
		if (((ft_timestamp()) - (x_time)) >= time)
			break ;
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		ret;

	if (argc != 5 && argc != 6)
		return (1);
	ret = ft_initialisation(&rules, argv);
	if (ret == 1)
		return (1);
	ft_program(&rules);
	return (0);
}
