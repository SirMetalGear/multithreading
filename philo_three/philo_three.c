/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:08:55 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/30 15:35:01 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		operate(t_all *all)
{
	int				i;
	struct timeval	tv;

	i = -1;
	gettimeofday(&tv, NULL);
	all->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (++i < all->philo.num)
	{
		all->thread_status = 0;
		fork_start(all, &all->pid, i);
		if (pthread_create(&all->thread[i], NULL, (void *)eat_status, all) != 0)
			return (1);
		if (pthread_create(&all->eat_thread[i], NULL, (void *)prev_eat_time,
																	all) != 0)
			return (1);
		while (all->thread_status != 1)
			usleep(10);
	}
	if (pthread_create(&all->monitor, NULL, (void *)monitor, all) != 0)
		return (1);
	i = -1;
	while (++i < all->philo.num)
		pthread_join(all->thread[i], NULL);
	pthread_join(all->monitor, NULL);
	return (0);
}

int		parse_data(int argc, char **argv, t_data *philo)
{
	if (argc < 5 || argc > 6 || all_num(argv) == 1)
	{
		printf("Arguments error\n");
		return (1);
	}
	philo->num = ft_atoi(argv[1]);
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	if (philo->num < 2 || philo->num > 200 || philo->die <= 60 ||
	philo->eat <= 60 || philo->sleep <= 60)
	{
		printf("ERROR: wrong argument\n");
		return (1);
	}
	if (argv[5] != 0)
	{
		philo->eat_times = ft_atoi(argv[5]);
		if (philo->eat_times == 0)
			return (1);
	}
	return (0);
}

int		struct_init(t_all *all)
{
	all->philo.num = 0;
	all->philo.eat = 0;
	all->philo.eat_times = 0;
	all->philo.sleep = 0;
	all->philo.die = 0;
	return (0);
}

int		main(int argc, char **argv)
{
	t_all	all;

	struct_init(&all);
	if (parse_data(argc, argv, &all.philo) == 1)
		return (1);
	if (fork_init(&all) == 1)
		return (1);
	if (operate(&all) == 1)
		return (1);
	cleaner(&all);
	return (0);
}
