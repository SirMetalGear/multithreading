/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:54:30 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/23 15:57:43 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			eat_status(t_all *all)
{
	int	i;

	i = all->turn;
	waitpid(all->pid[i], &all->pid_status[i], 0);
	return (0);
}

int			fork_start(t_all *all, pid_t **pid, int i)
{
	pid[0][i] = fork();
	if (pid[0][i] < 0)
	{
		printf("FORK FAILED. EXITING\n");
		exit(0);
	}
	if (pid[0][i] == 0)
		thread_start(all);
	return (0);
}

static int	massive_sem(t_all *all)
{
	int		i;
	char	*str;

	i = -1;
	if ((all->eat_sem = (sem_t **)calloc(all->philo.num + 1,
											sizeof(sem_t *))) == 0)
		return (1);
	while (++i < all->philo.num)
	{
		if ((str = ft_itoa(i + 200)) == 0)
			return (1);
		sem_unlink(str);
		if ((all->eat_sem[i] = sem_open(str, O_CREAT, 0666, 0)) == SEM_FAILED)
			return (1);
		free(str);
	}
	return (0);
}

static int	init_sem(t_all *all)
{
	sem_unlink("fork_sem");
	if ((all->fork_sem = sem_open("fork_sem", O_CREAT, 0666, all->philo.num))
																== SEM_FAILED)
		return (1);
	sem_unlink("write_sem");
	if ((all->write_sem = sem_open("write_sem", O_CREAT, 0666, 1))
																== SEM_FAILED)
		return (1);
	sem_unlink("turn_sem");
	if ((all->turn_sem = sem_open("turn_sem", O_CREAT, 0666, 1)) == SEM_FAILED)
		return (1);
	sem_unlink("time_sem");
	if ((all->time_sem = sem_open("time_sem", O_CREAT, 0666, 1)) == SEM_FAILED)
		return (1);
	if (massive_sem(all) == 1)
		return (1);
	return (0);
}

int			fork_init(t_all *all)
{
	if (init_sem(all) == 1)
		return (1);
	if ((all->thread = (pthread_t *)calloc(all->philo.num,
											sizeof(pthread_t))) == 0)
		return (1);
	if ((all->eat_thread = (pthread_t *)calloc(all->philo.num,
											sizeof(pthread_t))) == 0)
		return (1);
	if ((all->pid = (pid_t *)calloc(all->philo.num + 1,
											sizeof(pid_t))) == 0)
		return (1);
	if ((all->prev_eat = (long long *)calloc(all->philo.num,
											sizeof(long long))) == 0)
		return (1);
	if ((all->pid_status = (int *)calloc(all->philo.num, sizeof(int))) == 0)
		return (1);
	all->turn = 0;
	return (0);
}
