/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:52:29 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:16 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	prev_eat_time(t_all *all)
{
	int				i;
	int				turn;
	struct timeval	tv_mon;

	i = -1;
	sem_wait(all->turn_sem);
	turn = all->turn++;
	sem_post(all->turn_sem);
	pthread_detach(all->eat_thread[turn]);
	all->thread_status = 1;
	while (1)
	{
		sem_wait(all->eat_sem[turn]);
		all->prev_eat[turn] = get_time(all, &tv_mon);
	}
	return (0);
}

int	monitor(t_all *all)
{
	long long		current;
	struct timeval	tv_mon;
	int				i;

	i = 0;
	while (++i < all->philo.num && all->pid_status[i] != 256)
	{
		current = get_time(all, &tv_mon);
		if (current - all->prev_eat[i] >= all->philo.die)
		{
			philo_write(i, current, all, " is dead\n");
			sem_wait(all->write_sem);
			sem_wait(all->time_sem);
			i = -1;
			while (++i < all->philo.num)
				kill(all->pid[i], SIGINT);
			break ;
		}
		if (i == all->philo.num - 1)
		{
			i = -1;
			usleep(100);
		}
	}
	return (0);
}

int	monitor_and_struct_init(t_inside *inside, t_all *all)
{
	sem_wait(all->turn_sem);
	inside->turn = all->turn;
	sem_post(all->turn_sem);
	sem_post(all->eat_sem[inside->turn]);
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
	free(all->pid_status);
	free(all->pid);
	sem_close(all->fork_sem);
	sem_close(all->write_sem);
	sem_close(all->turn_sem);
	sem_close(all->time_sem);
	free(all->eat_sem);
	return (0);
}
