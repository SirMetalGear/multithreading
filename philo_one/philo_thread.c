/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:56:41 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/30 12:14:39 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	sleeping_time(t_all *all, t_inside *inside, long long *current_time)
{
	long long	wake_time;

	philo_write(inside->turn, *current_time, all, " is sleeping\n");
	wake_time = *current_time + all->philo.sleep;
	while (*current_time < wake_time && all->death_status != 1)
	{
		*current_time = get_time(all, &inside->tv);
		usleep(1000);
	}
	philo_write(inside->turn, *current_time, all, " is thinking\n");
}

static void	put_forks(t_all *all, t_inside *inside)
{
	pthread_mutex_unlock(&all->mutex[inside->turn]);
	if (inside->turn == all->philo.num - 1)
		pthread_mutex_unlock(&all->mutex[0]);
	else
		pthread_mutex_unlock(&all->mutex[inside->turn + 1]);
}

static void	eating_time(t_all *all, t_inside *inside, long long *current_time)
{
	long long		wake_time;

	wake_time = *current_time + all->philo.eat;
	while (*current_time < wake_time && all->death_status != 1)
	{
		*current_time = get_time(all, &inside->tv);
		usleep(1000);
	}
}

static void	taking_forks(t_all *all, t_inside *inside, long long *current_time)
{
	pthread_mutex_lock(&all->mutex[inside->turn]);
	*current_time = get_time(all, &inside->tv);
	philo_write(inside->turn, *current_time, all, " has taken a fork\n");
	if (inside->turn == all->philo.num - 1 && all->death_status != 1)
		pthread_mutex_lock(&all->mutex[0]);
	else if (all->death_status != 1)
		pthread_mutex_lock(&all->mutex[inside->turn + 1]);
	*current_time = get_time(all, &inside->tv);
	philo_write(inside->turn, *current_time, all, " has taken a fork\n");
	philo_write(inside->turn, *current_time, all, " is eating\n");
	all->prev_eat[inside->turn] = *current_time;
}

int			thread_start(t_all *all)
{
	t_inside		inside;
	int				i;
	long long		current_time;

	current_time = 0;
	i = 0;
	monitor_and_struct_init(&inside, all);
	while (all->death_status != 1)
	{
		taking_forks(all, &inside, &current_time);
		eating_time(all, &inside, &current_time);
		put_forks(all, &inside);
		i++;
		if (all->philo.eat_times != 0)
			if (i == all->philo.eat_times)
			{
				pthread_mutex_lock(&all->eat_mutex);
				all->eating_finished++;
				pthread_mutex_unlock(&all->eat_mutex);
			}
		if (all->death_status == 1)
			return (0);
		sleeping_time(all, &inside, &current_time);
	}
	return (0);
}
