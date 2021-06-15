/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:56:41 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/30 15:23:30 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

static void	put_forks(t_all *all)
{
	sem_post(all->fork_sem);
	sem_post(all->fork_sem);
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
	sem_wait(all->fork_sem);
	*current_time = get_time(all, &inside->tv);
	philo_write(inside->turn, *current_time, all, " has taken a fork\n");
	sem_wait(all->fork_sem);
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
		put_forks(all);
		i++;
		if (all->philo.eat_times != 0)
			if (i == all->philo.eat_times)
			{
				sem_wait(all->eat_sem);
				all->eating_finished++;
				sem_post(all->eat_sem);
			}
		if (all->death_status == 1)
			return (0);
		sleeping_time(all, &inside, &current_time);
	}
	return (0);
}
