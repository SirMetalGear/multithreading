/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:52:29 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/30 11:11:11 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	monitor(t_all *all)
{
	long long		current;
	int				i;

	i = 0;
	while (++i < all->philo.num)
	{
		if (all->eating_finished == all->philo.num)
		{
			all->death_status = 1;
			break ;
		}
		current = get_time(all, NULL);
		if (current - all->prev_eat[i] >= all->philo.die)
		{
			philo_write(i, current, all, " is dead\n");
			all->death_status = 1;
			break ;
		}
		if (i == all->philo.num - 1)
		{
			i = -1;
			usleep(10);
		}
	}
	return (0);
}

int	monitor_and_struct_init(t_inside *inside, t_all *all)
{
	pthread_mutex_lock(&all->turn_mutex);
	inside->turn = all->turn++;
	pthread_mutex_unlock(&all->turn_mutex);
	all->prev_eat[inside->turn] = get_time(all, &inside->tv);
	all->thread_status = 1;
	return (1);
}

int	philo_write(int turn, long long current_time, t_all *all, const char *str)
{
	pthread_mutex_lock(&all->write_mutex);
	if (all->death_status == 1)
	{
		pthread_mutex_unlock(&all->write_mutex);
		return (0);
	}
	ft_putnbr(current_time);
	write(1, " ", 1);
	ft_putnbr(turn + 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&all->write_mutex);
	return (0);
}

int	cleaner(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->philo.num)
		pthread_mutex_destroy(&all->mutex[i]);
	pthread_mutex_destroy(&all->write_mutex);
	pthread_mutex_destroy(&all->turn_mutex);
	pthread_mutex_destroy(&all->time_mutex);
	pthread_mutex_destroy(&all->eat_mutex);
	free(all->thread);
	free(all->prev_eat);
	free(all->mutex);
	return (0);
}
