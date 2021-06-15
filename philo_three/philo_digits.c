/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:56:55 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/30 15:34:40 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			all_num(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] > '9' || str[i][j] < '0')
				return (1);
		}
	}
	return (0);
}

int			ft_atoi(char *str)
{
	int num;

	num = 0;
	if (ft_strlen(str) > 10)
		return (-1);
	while (*str >= '0' && *str <= '9')
		num = num * 10 + (*str++ - '0');
	return (num);
}

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

long long	get_time(t_all *all, struct timeval *tv)
{
	long long		current_time;
	struct timeval	tv2;

	(void)tv;
	sem_wait(all->time_sem);
	gettimeofday(&tv2, NULL);
	current_time = (tv2.tv_sec * 1000 + tv2.tv_usec / 1000) - all->start_time;
	sem_post(all->time_sem);
	return (current_time);
}

void		ft_putnbr(ssize_t n)
{
	char				stroka[20];
	char				c;
	ssize_t				x;
	int					i;

	i = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	while (n != 0)
	{
		x = (n % 10);
		n = (n / 10);
		c = (x + '0');
		*(stroka + (i++)) = c;
	}
	while ((i--) != 0)
		write(1, (stroka + i), 1);
}
