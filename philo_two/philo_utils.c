/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:52:29 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/30 15:23:01 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	sem_wait(all->turn_sem);
	inside->turn = all->turn++;
	sem_post(all->turn_sem);
	all->prev_eat[inside->turn] = get_time(all, &inside->tv);
	all->thread_status = 1;
	return (1);
}

int	philo_write(int turn, long long current_time, t_all *all, const char *str)
{
	sem_wait(all->write_sem);
	if (all->death_status == 1)
	{
		sem_post(all->write_sem);
		return (0);
	}
	ft_putnbr(current_time);
	write(1, " ", 1);
	ft_putnbr(turn + 1);
	write(1, str, ft_strlen(str));
	sem_post(all->write_sem);
	return (0);
}

int	cleaner(t_all *all)
{
	int	i;

	i = -1;
	free(all->thread);
	free(all->prev_eat);
	sem_close(all->fork_sem);
	sem_close(all->write_sem);
	sem_close(all->turn_sem);
	sem_close(all->time_sem);
	return (0);
}
